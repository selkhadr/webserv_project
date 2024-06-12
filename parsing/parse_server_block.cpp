/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_server_block.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:16:46 by nel-mous          #+#    #+#             */
/*   Updated: 2024/06/12 11:44:30 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseConfig.hpp"

int ParseConfig::parse_server_block(std::ifstream& Confile, Server& server, std::string& line) 
{
    bool serverNameFound = false;
    int counter = 0;
    server = Server();
    std::getline(Confile, line);
   	if ((line.empty() || emptyline(line)) && handle_errors("Error: Empty line found.")) 
        return(1);
    if (opened_brace(line) == true) 
	{
        if (process_server_block(Confile, server, line, serverNameFound, counter))
            return (1);
    }
	else 
	{
        handle_errors("Error: Missing '{' after 'server' declaration.");
        return (1);
    }
    return (0);
}

int ParseConfig::process_server_block(std::ifstream& Confile, Server& server, std::string& line, bool& serverNameFound, int& counter) 
{
	bool inServer = true;
    bool ServerError = false;
    hostNameFound = false;
    std::vector<std::string> keys;
    while(std::getline(Confile, line)) 
    {
        if ((line.empty() || emptyline(line)) && handle_errors("Error: Empty line found.")) 
            return(1);
        if(is_comment(line))
            continue;
        if(closed_brace(line) == true)
        {
            inServer = false;
            if(ServerError && handle_errors("Error: Server directive value doesn't match the expected values."))
                return(1);
            if (server.GetServerDirectives().empty()) 
            {
                handle_errors("Error: No directives in 'Server' block.");
                    return (1);
            }
            if(!hostNameFound && handle_errors("Error: Missing 'hostname' key in the server block."))
                return(1);
            if(check_essential_directives(keys))
                return(1);
            m_servers.push_back(server);
            break;
        }
        if(is_location_directive(line) == false && closed_brace(line) == false)
        {
            if(has_semicolon(line))
                return(1);
			if (line_in_server_block(line, server, keys, serverNameFound, ServerError))
            	return (1);
        }
        else if(inServer && is_location_directive(line) == true)
        {
            counter++;
            if(semicolon_in_location(line))
                return(1);
            if(parse_location_block(Confile, server, line))
                return(1);
        }     
    }
    if(counter == 0 && handle_errors("No Location directives found in the server Block."))
        return(1);
    if(inServer && handle_errors("Error: Missing '}' at the end of the 'server' block."))
        return(1);  
    return (0);
}

int ParseConfig::line_in_server_block(std::string& line, Server &server,  std::vector<std::string> &keys, bool &serverNameFound, bool &ServerError)
{
	std::vector<std::string> values;
    std::string key, value;
    std::istringstream iss(line);
    iss >> key;
    if (!is_directive_allowed(key) )
    {
        handle_errors("Error: Directive '" + key + "' is not allowed.");
        return(1);
    }
    if(check_directive_in_server(key) == false)
        return(1);
    keys.push_back(key);
    
    if(key == "server_name")
    {
        if(serverNameFound && handle_errors("Error: Duplicate 'server_name' key in the server block."))
            return(1);
        serverNameFound = true;
    }
    if(key == "host_name")
    {
        if(hostNameFound && handle_errors("Error: Duplicate 'host_name' key in the server block."))
            return(1);
        hostNameFound = true;
    }
    while(iss >> value)
    {
        values.push_back(value);
        if(!is_value_valid(key, value, values))
            ServerError = true;
    }
    if(check_directives_size(key, values, 1))
        return (1);
    server.SetServerDirectives(key, values);
    default_port(server);
	return(0);
}