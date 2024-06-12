/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationDirectives.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:03:45 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:03:46 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationDirectives.hpp"
#include "../HttpRequestHandler.hpp"

LocationDirectives::LocationDirectives()
{
    
}

LocationDirectives::LocationDirectives(std::map<std::string, std::vector<std::string> > location_directives, std::multimap<std::string, std::vector<std::string> > server_from_config, int client_fd)
{
	std::map<std::string, std::vector<std::string> >::iterator it;
	std::multimap<std::string, std::vector<std::string> >::iterator ite;

    it =  location_directives.find("root");
    if (it != location_directives.end())
        root = it->second[0];
    else
    {
        ite =  server_from_config.find("root");
        if(ite != server_from_config.end())
            root = ite->second[0];
        else
            send_default_error_page(500, "Internal Server Error", client_fd);
    }
    it =  location_directives.find("redirect");
    if (it != location_directives.end())
        HTTP_redirection = it->second[0];
    it =  location_directives.find("autoindex");
    if (it != location_directives.end())
        autoindex = it->second[0];
    else
    {
        ite =  server_from_config.find("autoindex");
        if(ite != server_from_config.end())
            autoindex = ite->second[0];
        else
            autoindex = "off";
    }
    it =  location_directives.find("index_file");
    if (it != location_directives.end())
        index_file = it->second[0];
    else
    {
        ite =  server_from_config.find("index_file");
        if(ite != server_from_config.end())
            index_file = ite->second[0];
        else
            index_file = "index.html";
    }
    it =  location_directives.find("accepted_request_methods");
    if (it != location_directives.end())
    {
        std::vector<std::string>::iterator vect_it = it->second.begin();
        while(vect_it != it->second.end())
        {
            accepted_request_methods.push_back(*vect_it);
            vect_it++;
        }
    }
    else
    {
        ite =  server_from_config.find("accepted_request_methods");
        if (ite != server_from_config.end())
        {
            std::vector<std::string>::iterator vect_it = ite->second.begin();
            while(vect_it != ite->second.end())
            {
                accepted_request_methods.push_back(*vect_it);
                vect_it++;
            }
        }
        else
            send_default_error_page(500, "Internal Server Error", client_fd);
    }
    it =  location_directives.find("cgi_extension");
    if (it != location_directives.end())
        cgi_extension = it->second[0];
    else
    {
        ite =  server_from_config.find("cgi_extension");
        if(ite != server_from_config.end())
            cgi_extension = ite->second[0];
    }
    it =  location_directives.find("cgi_path");
    if (it != location_directives.end())
        cgi_path = it->second[0];
    else
    {
        ite =  server_from_config.find("cgi_path");
        if(ite != server_from_config.end())
            cgi_path = ite->second[0];
    }
    it =  location_directives.find("upload_directory");
    if (it != location_directives.end())
        upload_directory = it->second[0];
    else
    {
        ite =  server_from_config.find("upload_directory");
        if(ite != server_from_config.end())
            upload_directory = ite->second[0];
        else 
            upload_directory = "./upload_directory";
    }
}

void    LocationDirectives::set_root(std::string root)
{
    this->root = root;
}

void    LocationDirectives::set_accepted_request_methods(std::vector<std::string> accepted_request_methods)
{
    this->accepted_request_methods = accepted_request_methods;
}

void    LocationDirectives::set_HTTP_redirection(std::string HTTP_redirection)
{
    this->HTTP_redirection = HTTP_redirection;
}

void    LocationDirectives::set_autoindex(std::string autoindex)
{
    this->autoindex = autoindex;
    
}

void    LocationDirectives::set_index_file(std::string index_file)
{
    this->index_file = index_file;
    
}

std::string &LocationDirectives::get_root()
{
    return root;
}

std::vector<std::string> &LocationDirectives::get_accepted_request_methods()
{
    return accepted_request_methods;
}

std::string &LocationDirectives::get_HTTP_redirection()
{
    return HTTP_redirection;
}

std::string &LocationDirectives::get_autoindex()
{
    return autoindex;
}

std::string &LocationDirectives::get_index_file()
{
    return index_file;
}

std::string    &LocationDirectives::get_cgi_extension()
{
    return (cgi_extension);
}

std::string    &LocationDirectives::get_cgi_path()
{
    return (cgi_path);
}

std::string    &LocationDirectives::get_upload_directory()
{
    return (upload_directory);
}