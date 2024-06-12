/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directive.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:08:49 by nel-mous          #+#    #+#             */
/*   Updated: 2024/06/12 11:48:24 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseConfig.hpp"

int ParseConfig::has_semicolon(std::string &line)
{
    if (line.back() == ';')
        line = line.substr(0, line.size() - 1);
    else
    {
        // handle_errors("Error: Missing ';' at the end of the line: " + line);
        return (1);
    }
    return(0);
}

int ParseConfig::semicolon_in_location(std::string &line)
{
    if(line.back() == ';')
        return(1);
    return(0);
}

int ParseConfig::check_braces_balance() 
{
    if ((open_location_count != close_location_count)) 
        return (1);
    return (0);
}
std::string ParseConfig::remove_comment(const std::string& line)
{
    std::size_t pos = line.find("#");
    if (pos != std::string::npos)
        return (line.substr(0, pos));
    return (line);
}

bool ParseConfig::is_comment(const std::string &line) 
{
    std::string subline;
    size_t first = line.find_first_not_of(' ');

    if (first == std::string::npos)
        return (false);
    else
        subline = line.substr(first);
    return (subline[0] == '#');
}

bool ParseConfig::closed_brace(const std::string &line)
{
    size_t first = line.find_first_not_of(' ');
    size_t last = line.find_last_not_of(' ');

    if (first != std::string::npos) 
    {
        if (first == last) 
        {
            if (line[first] == '}') 
                return (true);
            else
                return (false);
        } 
        else
            return (false);
    } 
    return(false);
}

bool ParseConfig::opened_brace(const std::string &line)
{
    size_t first = line.find_first_not_of(' ');
    size_t last = line.find_last_not_of(' ');

    if (first != std::string::npos) 
    {
        if (first == last) 
        {
            if (line[first] == '{') 
                return (true);
            else
                return (false);
        } 
        else
            return (false);
    } 
    return(false);
}

bool ParseConfig::is_integer(const std::string& str) 
{
    if (str.empty()) 
        return (false);
    size_t i = 0;
    while ( i < str.size()) 
    {
        if (!std::isdigit(str[i])) 
            return (false);
        i++;
    }
    return (true);
}

bool ParseConfig::is_value_valid(const std::string& key, const std::string& value, const std::vector<std::string>& values)
{
    if (key == "error") 
    {
        if (!is_integer(values[0])) 
            return (false);
    }
    else if(key == "body_max_size")
    {
        if(!is_integer(values[0]))
            return(false);
    }
    else if(key == "execution_time_limit")
    {
        if(!is_integer(values[0]))
            return(false);
    }
    else if(key == "port")
    {
        if(!is_integer(values[0]))
            return(false);
    }
    else if(key == "autoindex")
        return(value == "on" || value == "off" || value == "true" || value == "false");
    else if(key == "accepted_request_methods")
        return(value == "POST" || value == "DELETE" || value == "GET"); 
    else
    {
        if(special_character(value))
            return(false);
    }
	return(true); 
}

bool ParseConfig::is_server(const std::string &line)
{
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;
    while(iss >> token)
        tokens.push_back(token);
    if(tokens.size() == 1 && tokens[0] == "server")
        return(true);
    return(false);
}

bool ParseConfig::is_location_directive(const std::string& line)
{
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;
    while(iss >> token)
        tokens.push_back(token);
    if(tokens.size() == 2 && tokens[0] == "location")
        return(true);
    return(false);
}

bool ParseConfig::special_character(const std::string& value)
{
    for(size_t i = 0; i < value.size(); i++)
    {
        char c = value[i];
        if(!isalnum(c) && c != '_' && c != '-' && c != '/' && c != ':' && c != '.')
            return (true);
    }
    return (false);
}

bool ParseConfig::emptyline(const std::string& str) 
{
    size_t i = 0;
    while (i < str.length()) 
    {
        if (str[i] != ' ' && str[i] != '\t')
            return (false);
        i++;
    }
    return (true);
}

bool ParseConfig::handle_errors(const std::string& errorMessage)
{
    std::cout << errorMessage << std::endl;
    return (true);
}

bool ParseConfig::is_directive_allowed(const std::string& directive) 
{
    size_t i = 0;
    while(i < _AllowedDirectives.size()) 
    {
        if(_AllowedDirectives[i] == directive)
            return (true);
        i++;
    }
    return (false);
}

bool ParseConfig::check_directive_in_location(std::string &directive)
{
    if(directive == "body_max_size" || directive == "error" || directive == "execution_time")
    {
        std::cout << "Error: Directive " << directive << " should not be in the location block." << std::endl;
        return(false);
    }
    return(true);
}

bool ParseConfig::check_directive_in_server(std::string &directive)
{
    if(directive == "redirect")
    {
        std::cout << "Error: Directive " << directive << " should not be in the server block." << std::endl;
        return(false);
    }
    return(true);
}
int ParseConfig::check_directives_size(std::string key, std::vector<std::string> values, int check)
{
	if (key !=  "accepted_request_methods"  && key != "error")
        if(values.size() != 1 && handle_errors("number of values not as expected!"))
            return (1);
    if (key == "accepted_request_methods")
        if((!values.size() ||  values.size() >= 4) && handle_errors("number of values of the 'accepted_request_methods' key not as expected!"))
            return (1);
    if (check && key == "error")
        if(values.size() != 2 && handle_errors("number of values of the 'error' key not as expected!"))
            return (1);
	return (0);
}

int ParseConfig::check_essential_directives(std::vector<std::string> keys)
{
    int count = 0;
    for (size_t i = 0; i < keys.size(); i++)
    {
        if (keys[i] == "host_name" || keys[i] == "body_max_size" || keys[i] == "location")
            count++;  
    }
    if (count >= 4)
    {
        handle_errors("Error: The server's directives are insufficient.");
        return 1;
    }
    return(0);
}


int ParseConfig::check_directive(const std::vector<Server>& Servers, const std::vector<Location> &Locations) 
{
    size_t i = 0;
    size_t j;
    while(i < Servers.size()) 
    {
        j = 0;
        const std::multimap<std::string, std::vector<std::string> >& serverDirectives = Servers[i].GetServerDirectives();
        std::multimap<std::string, std::vector<std::string> >::const_iterator s_it = serverDirectives.begin();
        while(s_it != serverDirectives.end()) 
        {
            std::string s_Key = s_it->first;
            if(!is_directive_allowed(s_Key) && handle_errors("Error: Unexpected directive found."))
                return 1;
            s_it++;
        }
        while (j < Locations.size())
        {
            const std::map<std::string, std::vector<std::string> >& locationDirectives = Locations[j].GetLocationDirectives();
            std::map<std::string, std::vector<std::string> >::const_iterator l_it = locationDirectives.begin();
            while(l_it != locationDirectives.end()) 
            {
                std::string l_Key = l_it->first;
                if(!is_directive_allowed(l_Key) && handle_errors("Error: Unexpected directive found."))
                    return 1;
                l_it++;
            }
            j++;
        }
        i++;
    }
    return 0;
}