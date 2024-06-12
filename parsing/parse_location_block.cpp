/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_location_block.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:12:26 by nel-mous          #+#    #+#             */
/*   Updated: 2024/06/06 14:29:18 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseConfig.hpp"

int ParseConfig::parse_location_block(std::ifstream& Confile, Server& server, std::string& line) 
{
    std::string locationkey, pathValue;
    std::istringstream iss(line);
    iss >> locationkey >> pathValue;
    Location location;
    location.SetPath(pathValue);
    std::getline(Confile, line);
    if ((line.empty() || emptyline(line)) && handle_errors("Error: Empty line found."))
        return(1);
    if (opened_brace(line) == true) 
    {
        open_location_count++;
        if (process_location_block(Confile, server, location, line))
            return (1);
        if (location.GetLocationDirectives().empty()) 
        {
            handle_errors("Error: No directives in 'Location' block.");
                return (1);
        }
    }
    else 
    {
        handle_errors("Error: Missing '{' after 'Location' declaration.");
        return (1);
    }
    return (0);
}

int ParseConfig::process_location_block(std::ifstream& Confile, Server& server, Location& location, std::string& line)
{
    bool LocationError = false;
    bool inLocation = true;
    bool prevLocationClosed = true;
    while(std::getline(Confile, line)) 
	{
        if ((line.empty() || emptyline(line)) && handle_errors("Error: Empty line found.")) 
            return(1);
        if(is_comment(line))
            continue;
        if(closed_brace(line) == true)
		{
            close_location_count++;
            inLocation = false;
            if(prevLocationClosed)
            {
                _locations.push_back(location);
                if(LocationError)
                    return(1);
                server.AddLocation(location);
            }
            else 
            {
                handle_errors("Error: Location block not closed before starting a new Location block.");
                return(1);
            }
            break;
        }
        if(has_semicolon(line))
            return(1);
        if(line_in_location_block(line, location, LocationError, prevLocationClosed, inLocation))
            return(1);
    }
    if(check_braces_balance())
        return(1);
    if(inLocation && handle_errors("Error: Missing '}' at the end of the 'Location' block."))
        return(1);    
    return(0);
}


int ParseConfig::line_in_location_block(std::string& line, Location& location, bool& LocationError, bool& prevLocationClosed, bool inLocation) 
{
    std::vector<std::string> values;
    std::string key, value;
    std::istringstream iss(line);
    iss >> key;
    if (!is_directive_allowed(key))
    {
        handle_errors("Error: Directive '" + key + "' is not allowed.");
        // LocationError = true;
        return (1);
    }
    
    // check directive in location (body_max_size and execution_time and error must not be in location block)
    if(check_directive_in_location(key) == false)
        return(1);
    while (iss >> value)
    {
        values.push_back(value);
        if(!is_value_valid(key, value, values))
            LocationError = true;
    }
    if(check_directives_size(key, values, 1))
    {
        LocationError = true;
        return(1);
    }      
    location.SetLocationDirectives(key, values);
    if(inLocation && is_location_directive(line) == true)
        prevLocationClosed = false; 
    return(0);
}
