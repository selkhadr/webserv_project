/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:46:42 by nel-mous          #+#    #+#             */
/*   Updated: 2024/06/08 19:10:35 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER
#define SERVER

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include "Location.hpp"

class Server 
{
    private:
        std::vector<Location> m_locations;
        std::multimap<std::string, std::vector<std::string> > m_Serverdirectives;
        bool _check;

    public:
        Server();
        ~Server();
        bool GetCheck();
        void SetCheck(bool value);
        void SetServerDirectives(const std::string &key, const std::vector<std::string> &values);
        std::multimap<std::string, std::vector<std::string> >   GetServerDirectives() const;
        std::vector<Location> GetLocations() const;
        void AddLocation(const Location &location);
        void PrintServerDirectives() const;
        std::vector<std::string>  getValues(std::vector<std::string> &ports) const;
        std::vector<std::string>  getHosts(std::vector<std::string> &ports) const;
        // bool _check;
};

#endif