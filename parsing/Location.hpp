/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:46:34 by nel-mous          #+#    #+#             */
/*   Updated: 2024/05/30 15:45:12 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION
#define LOCATION

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

class Location 
{
    private:
        std::string m_path;
        std::map<std::string, std::vector<std::string> > m_Locationdirectives;

    public:
        Location();
        ~Location();
        void SetPath(std::string path);
        std::string GetPath() const;
        std::map<std::string, std::vector<std::string> > GetLocationDirectives() const;
        void SetLocationDirectives(const std::string &key, const std::vector<std::string> &values);
        void PrintLocationDirectives() const;
};

#endif