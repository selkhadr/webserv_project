/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseConfig_utils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:08:55 by nel-mous          #+#    #+#             */
/*   Updated: 2024/06/12 11:47:12 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseConfig.hpp"
#include "../HttpRequestHandler/HttpRequestHandler.hpp"

Server ParseConfig::getserver_by_port(std::string port_value, ParseConfig &Config, int client_fd)
{
    std::string port;
    Server server;
    std::vector<Server> servers = Config.GetServers();
    size_t i = 0; 

    while(i < servers.size())
    {
        std::multimap<std::string, std::vector<std::string> > directives = servers[i].GetServerDirectives();
        std::multimap<std::string, std::vector<std::string> >::iterator it = directives.begin();
        while (it != directives.end())
        {
            if (it->first == "port")
            {
                if(it->second[0] == port_value)
                {
                    server = servers[i];
                    return (server);
                }
            }
            it++;
        }
        i++;
    }
    send_default_error_page(400, "Bad Request", client_fd);
    return Server();
}

void ParseConfig::default_port(Server &server)
{
    std::multimap<std::string, std::vector<std::string> > server_directives = server.GetServerDirectives();
    std::multimap<std::string, std::vector<std::string> >::iterator it = server_directives.find("port");
    if (it == server_directives.end())
    {
        std::vector<std::string> vect;
        vect.push_back("80");
        server.SetServerDirectives("port", vect);
    }
}
