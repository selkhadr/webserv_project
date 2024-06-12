/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:09:49 by sbellafr          #+#    #+#             */
/*   Updated: 2024/06/12 13:14:38 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

webserv::webserv(int port, std::string address)
{
    this->port = port;
    this->address = address;
}
webserv::webserv()
{

}
webserv::~webserv()
{
}
/*Methodes*/
int webserv::get_port()
{
    return this->port;
}
std::string webserv::get_address()
{
    return this->address;
}
in_addr_t custom_inet_addr(const std::string &address)
{
    unsigned int bytes[4];
    char dot;
    std::stringstream ss(address);
    ss >> bytes[0] >> dot >> bytes[1] >> dot >> bytes[2] >> dot >> bytes[3];

    for (int i = 0; i < 4; ++i)
    {
        if (bytes[i] > 255)
        {
            return INADDR_NONE;
        }
    }

    in_addr_t addr = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
    return htonl(addr); // Convert to network byte order
}
void webserv::socket_create()
{
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    this->ser_fd = socket(AF_INET, SOCK_STREAM, 0);
    int flags = fcntl(this->ser_fd, F_GETFL, 0);
    fcntl(this->ser_fd, F_SETFL, flags | O_NONBLOCK);
    int enable = 1;
    if (setsockopt(this->ser_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    {
        throw std::runtime_error("Setting socket options failed");
    }

    /*parse from conf file later*/
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = custom_inet_addr(this->address.c_str());
    server_address.sin_port = htons(port);
    // std::cout << "port: " << this->get_port() << std::endl;
    // std::cout << "address: " << this->get_address() << std::endl;
    if (bind(this->ser_fd, reinterpret_cast<struct sockaddr *>(&server_address), sizeof(server_address)) < 0)
    {
        throw std::runtime_error("Binding failed");
    }

    if (listen(this->ser_fd, 50) < 0)
    {
        throw std::runtime_error("Listening failed");
    }
}
int webserv::get_ser_fd()
{
    return this->ser_fd;
}

struct sockaddr_in &webserv::addr_get()
{
    return this->addr;
}

void webserv::handleClientRequest(Request &request, std::vector<webserv> &server, std::vector<Clients> &clients, int &max, fd_set &read_fd_set, fd_set &write_fd_set, int i, bool &chunked_finished)
{
    int ser_choice = request.server_choice(server, server.size(), i);
    if (ser_choice != -1)
    {
        socklen_t client_addr_len = sizeof(server[ser_choice].addr_get());
        Clients tmp;
        tmp.client_fd = accept(server[ser_choice].get_ser_fd(), reinterpret_cast<struct sockaddr *>(&server[ser_choice].addr_get()), &client_addr_len);
        fcntl(tmp.client_fd, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
        FD_SET(tmp.client_fd, &read_fd_set);
        if (tmp.client_fd > max)
            max = tmp.client_fd;
        tmp.total = 0;
        tmp.bytes_received = 0;
        tmp.total_sent = 0;
        clients.push_back(tmp);
    }
    else
    {
        Clients *user = NULL;
        for (size_t j = 0; j < clients.size(); j++)
        {
            if (clients[j].client_fd == i)
            {
                user = &clients[j];
                break;
            }
        }
        char *buffer;
        buffer = new char[1024];
        bzero(buffer, 1024);
        user->received = recv(user->client_fd, buffer, 1024, 0);
        if (user->received == -1)
        {
            std::cerr << "Error receiving data from socket" << std::endl;
            return;
        }
        else if (user->received == 0)
        {
            FD_CLR(user->client_fd, &read_fd_set);
            close(user->client_fd);
            return;
        }
        user->bytes_received += user->received;
        user->bufferprint.append(buffer, user->received);
        delete[] buffer;
        if (user->bufferprint.find("Transfer-Encoding: chunked") != std::string::npos && request.RequestName(user->bufferprint) == 1)
        {
            if (user->bufferprint.find("\r\n0\r\n\r\n") != std::string::npos)
            {
                chunked_finished = true;
            }
            if (chunked_finished)
            {
                FD_CLR(user->client_fd, &read_fd_set);
                FD_SET(user->client_fd, &write_fd_set);
                chunked_finished = false;
            }
        }
        else if (request.RequestName(user->bufferprint) == 1 && user->total == 0)
        {
            user->total = request.calculate_content_length(user->bufferprint) + request.find_header_end(user->bufferprint);
        }
        if ((((request.RequestName(user->bufferprint) == 1) && (user->bytes_received >= user->total)) || request.RequestName(user->bufferprint) == 2 || request.RequestName(user->bufferprint) == 3) &&
            !(user->bufferprint.find("Transfer-Encoding: chunked") != std::string::npos))
        {

            FD_CLR(user->client_fd, &read_fd_set);
            FD_SET(user->client_fd, &write_fd_set);
        }
    }
}
void webserv::processClient(std::vector<Clients> &clients, fd_set &write_fd_set, int i, ParseConfig &Config)
{
    Clients *user = NULL;
    int userpos = 0;
    for (size_t j = 0; j < clients.size(); j++)
    {
        if (clients[j].client_fd == i)
        {
            userpos = j;
            user = &clients[j];
            break;
        }
    }
    send_http_request(user->client_fd, Config, user->bufferprint, user->bytes_received);
    FD_CLR(user->client_fd, &write_fd_set);
    close(user->client_fd);
    clients.erase(clients.begin() + userpos);
}