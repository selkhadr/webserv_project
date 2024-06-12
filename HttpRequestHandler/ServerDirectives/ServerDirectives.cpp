/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerDirectives.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:24:58 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 13:13:41 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerDirectives.hpp"

ServerDirectives::ServerDirectives()
{
    
}

ServerDirectives::ServerDirectives(std::multimap<std::string, std::vector<std::string> > server_from_config)
{
    std::multimap<std::string, std::vector<std::string> >::iterator it = server_from_config.begin();

    while (it != server_from_config.end())
    {
        if(it->first == "error")
            error_pages.insert(std::make_pair(atoi(it->second[0].c_str()), it->second[1]));
        it++;
    }
    default_error_page = "./error_pages/default_error_page.html";
    it =  server_from_config.find("execution_time_limit");
    if (it != server_from_config.end())
        execution_time_limit = atoi(it->second[0].c_str());
    else
        execution_time_limit = 10;
    it =  server_from_config.find("body_max_size");
    if (it != server_from_config.end())
        body_max_size = atoi(it->second[0].c_str());
    else 
        body_max_size = 10000000;
}

std::map<int, std::string> &ServerDirectives::get_error_pages()
{
    return (error_pages);
}

std::string ServerDirectives::get_default_error_page()
{
    return (default_error_page);
}

double    &ServerDirectives::get_execution_time_limit()
{
    return execution_time_limit;
}
double    &ServerDirectives::get_body_max_size()
{
    return body_max_size;
}