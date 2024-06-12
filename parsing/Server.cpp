/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:46:39 by nel-mous          #+#    #+#             */
/*   Updated: 2024/06/08 19:12:37 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(): _check(0)
{
    
}

Server::~Server()
{

}

bool Server::GetCheck()
{
    return(this->_check);
}

void Server::SetCheck(bool value) 
{
    _check = value;
}

std::multimap<std::string, std::vector<std::string> > Server::  GetServerDirectives() const
{
	return(this->m_Serverdirectives);
}

void Server::SetServerDirectives(const std::string& key, const std::vector<std::string>& values) 
{
      m_Serverdirectives.insert(std::make_pair(key, values));
}

std::vector<Location> Server::GetLocations() const
{
	return(this->m_locations);
}

void Server::AddLocation(const Location& location) 
{
    this->m_locations.push_back(location);
}

void Server::PrintServerDirectives() const
{
    std::multimap<std::string, std::vector<std::string> > serverdirectives = GetServerDirectives();
    std::multimap<std::string, std::vector<std::string> >::const_iterator it = serverdirectives.begin();
    while (it != serverdirectives.end())
    {
        std::cout << "    Serverkey => " << it->first << ", ";
        std::cout << "ServerValues => ";

        const std::vector<std::string>& values = it->second;
        size_t i = 0;
        while (i < values.size())
        {
            std::cout << values[i] << " ";
            i++;
        }
        std::cout << std::endl;
        it++;
    }
}
std::vector<std::string> Server::getValues(std::vector<std::string>& ports) const
{
    std::multimap<std::string, std::vector<std::string> > serverdirectives = GetServerDirectives();
    std::multimap<std::string, std::vector<std::string> > ::const_iterator it = serverdirectives.begin();

    while (it != serverdirectives.end())
    {
        if (it->first == "port")
        {

            const std::vector<std::string> &values = it->second;
            size_t i = 0;
            while (i < values.size())
            {
                ports.push_back(values[i]);
                i++;
            }
        }

        it++;
    }
    return ports;
}
std::vector<std::string> Server::getHosts(std::vector<std::string>& hostNames) const
{
    std::multimap<std::string, std::vector<std::string> > serverdirectives = GetServerDirectives();
    std::multimap<std::string, std::vector<std::string> > ::const_iterator it = serverdirectives.begin();
    
    while (it != serverdirectives.end())
    {

         if (it->first == "host_name")
        {
            const std::vector<std::string> &values = it->second;
            size_t i = 0;
            while (i < values.size())
            {
                 hostNames.push_back(values[i]);

                i++;
            }
        }

        it++;
    }
    return hostNames;
}