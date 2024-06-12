/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingBridge.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:11:57 by sbellafr          #+#    #+#             */
/*   Updated: 2024/06/12 12:31:38 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsingBridge.hpp"
parsingBridge::parsingBridge(char **av, ParseConfig Config) 
{
    this->Config = Config;
    this->av = av;
}

parsingBridge::~parsingBridge()
{
}

std::vector<webserv> parsingBridge::serverConfiger()
{
  
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
            std::string hostName = serverHostNames[i];
            server.push_back(webserv(port, hostName));
        }
        hostNames.insert(hostNames.end(), serverHostNames.begin(), serverHostNames.end());
        ports.insert(ports.end(), serverPorts.begin(), serverPorts.end());
    }
    return server;
}
