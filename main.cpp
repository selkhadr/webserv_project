/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:09:49 by sbellafr          #+#    #+#             */
/*   Updated: 2024/06/12 12:12:28 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetClass/GetClass.hpp"
#include "PostClass/PostClass.hpp"
#include "DeleteClass/DeleteClass.hpp"
#include "webserv.hpp"
#define IDLE_TIMEOUT
#include <sys/select.h>
#include "parsing/ParseConfig.hpp"
#include <unistd.h>
#include <fcntl.h>
#include "HttpRequestHandler/HttpRequestHandler.hpp"

bool check_chunked(std::string buffer)
{
    size_t pos = buffer.find("\r\n0\r\n\r\n");
    if (pos != std::string::npos)
    {
        return true;
    }
    return false;
}

int send_http_request(int client_fd, ParseConfig &config, std::string http_request, int recv_value)
{
    std::string http_method = http_request.substr(0, 7);

    try
    {
        if (!http_method.find("GET"))
            handle_get_method(recv_value, http_request, client_fd, config);
        else if (!http_method.find("POST"))
            handle_post_method(recv_value, http_request, client_fd, config);
        else if (!http_method.find("DELETE"))
            handle_delete_method(recv_value, http_request, client_fd, config);
        else
            send_default_error_page(405, "Method Not Allowed", client_fd);
    }
    catch (const FlowControlException &e)
    {
        if (e.get_flag() == 1)
            return 1;
    }
    return 0;
}

void perfect_server()
{
    int max = 0;
    while (max < MAX_SIZE)
    {
        max++;
    }
}
// #define BUFFER_SIZE 1024
int main(int ac, char **av)
{
    if (ac == 2)
    {

        bool chunked_finished = false;
        ParseConfig Config;
        fd_set read_fd_set;  // Separate sets for read and write file descriptors
        fd_set write_fd_set; // Separate sets for read and write file descriptors
        FD_ZERO(&read_fd_set);
        FD_ZERO(&write_fd_set);
        Request request;
        signal(SIGPIPE, SIG_IGN);
        std::vector<webserv> server;
        int max = 0;
        // khas nktbou erreuer
        if (Config.readfile(av[1]))
            return (1);
        const std::vector<Server> &servers = Config.GetServers();
        std::vector<std::string> hostNames;
        std::vector<std::string> ports;
        for (size_t i = 0; i < servers.size(); i++)
        {
            std::vector<std::string> serverPorts;
            std::vector<std::string> serverHostNames;

            servers[i].getValues(serverPorts);
            servers[i].getHosts(serverHostNames);

            for (size_t j = 0; j < serverPorts.size(); j++)
            {
                int port = std::atoi(serverPorts[j].c_str());
                std::string hostName = serverHostNames[j];
                server.push_back(webserv(port, hostName));
            }
            hostNames.insert(hostNames.end(), serverHostNames.begin(), serverHostNames.end());
            ports.insert(ports.end(), serverPorts.begin(), serverPorts.end());
        }

        for (size_t i = 0; i < server.size(); i++)
        {
            try
            {
                server[i].socket_create();
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
            max = server[i].get_ser_fd();
            FD_SET(server[i].get_ser_fd(), &read_fd_set);
        }
        std::vector<Clients> clients;
        while (1)
        {
            int c = 0;
            fd_set tmp_read_fd_set;  // Separate sets for temporary read and write FD sets
            fd_set tmp_write_fd_set; // Separate sets for temporary read and write FD sets
            FD_COPY(&read_fd_set, &tmp_read_fd_set);
            FD_COPY(&write_fd_set, &tmp_write_fd_set);
            select(max + 1, &tmp_read_fd_set, &tmp_write_fd_set, NULL, 0); // Include both read and write FD sets
            for (int i = 0; i < max + 1; i++)
            {
                if (FD_ISSET(i, &tmp_read_fd_set))
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
                            break;
                        }
                        else if (user->received == 0)
                        {
                            FD_CLR(user->client_fd, &read_fd_set);
                            close(user->client_fd);
                            break;
                        }
                        user->bytes_received += user->received;
                        // check if is chunked finished
                        user->bufferprint.append(buffer, user->received);
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

                        c++;
                    }
                }
                if (FD_ISSET(i, &tmp_write_fd_set))
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
                perfect_server();
            }
        }
    }
}