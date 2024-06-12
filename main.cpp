/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:09:49 by sbellafr          #+#    #+#             */
/*   Updated: 2024/06/12 13:06:08 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "webserv.hpp"
#include "parsingBridge.hpp"

int main(int ac, char **av)
{
    if (ac > 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    else
    {
        fd_set read_fd_set;
        fd_set write_fd_set;
        FD_ZERO(&read_fd_set);
        FD_ZERO(&write_fd_set);
        Request request;
        signal(SIGPIPE, SIG_IGN);
        ParseConfig Config;

        std::string str = "parsing/nginx1.conf";

        char *filename = av[1];
        if (ac == 1)
            filename = (char *)str.c_str();

        if (Config.readfile(filename))
            return (1);

        parsingBridge bridge(av, Config);
        std::vector<webserv> server = bridge.serverConfiger();
        int max = 0;
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
            if (server[i].get_ser_fd() > max)
                max = server[i].get_ser_fd();
            FD_SET(server[i].get_ser_fd(), &read_fd_set);
        }
        bool chunked_finished = false;
        std::vector<Clients> clients;
        webserv recvsend;
        while (1)
        {
            fd_set tmp_read_fd_set;
            fd_set tmp_write_fd_set;
            FD_COPY(&read_fd_set, &tmp_read_fd_set);
            FD_COPY(&write_fd_set, &tmp_write_fd_set);
            timeval timeout;
            timeout.tv_sec = 30;
            timeout.tv_usec = 0;
            int selected = select(max + 1, &tmp_read_fd_set, &tmp_write_fd_set, NULL, &timeout);
            if(selected < 0)
                break;
            for (int i = 0; i < max + 1; i++)
            {
                if (FD_ISSET(i, &tmp_read_fd_set))
                    recvsend.handleClientRequest(request, server, clients, max, read_fd_set,
                         write_fd_set, i, chunked_finished);
                if (FD_ISSET(i, &tmp_write_fd_set))
                    recvsend.processClient(clients, write_fd_set, i, Config);
                perfect_server();
            }
        }
    }
    return 0;
}
