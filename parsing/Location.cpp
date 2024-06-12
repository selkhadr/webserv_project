/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:46:30 by nel-mous          #+#    #+#             */
/*   Updated: 2024/06/06 15:44:17 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "ParseConfig.hpp"

Location::Location()
{

}

Location::~Location()
{

}

std::string Location::GetPath() const
{
	return(this->m_path);
}

void Location::SetPath(std::string path)
{
	this->m_path = path;
}

std::map<std::string, std::vector<std::string> > Location::GetLocationDirectives() const
{
    return(this->m_Locationdirectives);
}

void Location::SetLocationDirectives(const std::string &key, const std::vector<std::string>& values)
{
    m_Locationdirectives.insert(std::make_pair(key, values));
}

void Location::PrintLocationDirectives() const
{
    std::map<std::string, std::vector<std::string> > locationdirectives = GetLocationDirectives();
    std::map<std::string, std::vector<std::string> >::const_iterator it = locationdirectives.begin();
    while(it != locationdirectives.end())
    {
        std::cout << "    Locationkey => " << it->first << ", ";
        std::cout << "LocationValues => ";

        const std::vector<std::string>& values = it->second;
        size_t i = 0;
        while(i < values.size())
        {
            std::cout << values[i] << " ";
            i++;
        }
        std::cout << std::endl;
        it++;
    }
}