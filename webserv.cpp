/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:09:49 by sbellafr          #+#    #+#             */
/*   Updated: 2024/06/07 19:03:49 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

webserv::webserv(int port, std::string address)
{
    this->port = port;
    this->address = address;
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

void webserv::socket_create()
{
    struct sockaddr_in server_address;
    /*CHECK*/
    memset(&server_address, 0, sizeof(server_address));

    this->ser_fd = socket(AF_INET, SOCK_STREAM, 0);

    int flags = fcntl(this->ser_fd, F_GETFL, 0);
    fcntl(this->ser_fd, F_SETFL, flags | O_NONBLOCK);
    fcntl(this->ser_fd, F_SETFL, O_NONBLOCK | FD_CLOEXEC);
    int enable = 1;
    if (setsockopt(this->ser_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    {
        throw std::runtime_error("Setting socket options failed");
    }

    /*parse from conf file later*/
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);
    this->addr_get() = server_address;
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
