/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseConfig.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:35:52 by nel-mous          #+#    #+#             */
/*   Updated: 2024/06/12 11:45:50 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseConfig.hpp"

std::vector<std::string> ParseConfig::_AllowedDirectives;

bool ParseConfig::hostNameFound = false;

void ParseConfig::initialize_allowed_directives() 
{
    _AllowedDirectives.push_back("port");
    _AllowedDirectives.push_back("error");
    _AllowedDirectives.push_back("server_name");
    _AllowedDirectives.push_back("location");
    _AllowedDirectives.push_back("autoindex");
    _AllowedDirectives.push_back("root");
    _AllowedDirectives.push_back("accepted_request_methods");
    _AllowedDirectives.push_back("redirect");
    _AllowedDirectives.push_back("cgi_path");
    _AllowedDirectives.push_back("cgi_extension");
    _AllowedDirectives.push_back("index_file");
    _AllowedDirectives.push_back("host_name");
    _AllowedDirectives.push_back("body_max_size");
    _AllowedDirectives.push_back("upload_directory");
    _AllowedDirectives.push_back("execution_time_limit");
}

ParseConfig::ParseConfig():open_location_count(0), close_location_count(0)
{
    initialize_allowed_directives();
}

ParseConfig::~ParseConfig()
{

}

std::vector<Server> ParseConfig::GetServers() const 
{
    return (this->m_servers);
}

int ParseConfig::readfile(const std::string& filename)
{
    std::ifstream Confile(filename);
    if (!Confile.is_open() && handle_errors("Cannot open the file! "))
        return (1);
    std::string line;
    Server server;
    while(std::getline(Confile, line)) 
    {
        if ((line.empty() || emptyline(line)) && handle_errors("Error: Empty line found.")) 
            return(1);
        if(is_comment(line))
            continue;
        if(is_server(line) == true)
        {
            if(parse_server_block(Confile, server, line))
                return(1);
        }
        else 
        {
            std::cout << "Error : is not a server Block" << std::endl;
            return(1);
        }
    }
    // Confile.close();
    return(0);
}

