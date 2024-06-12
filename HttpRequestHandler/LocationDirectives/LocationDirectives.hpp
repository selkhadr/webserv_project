/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationDirectives.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:04:16 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:04:17 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LocationDirectives_HPP
#define LocationDirectives_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <stdexcept>

class LocationDirectives
{
private:
    std::string                 root;
    std::vector<std::string>    accepted_request_methods;
    std::string                 HTTP_redirection;
    std::string                 autoindex;
    std::string                 index_file;
    std::string                 cgi_extension;
    std::string                 cgi_path;
    std::string                 upload_directory;
public:
    LocationDirectives();
    LocationDirectives(std::map<std::string, std::vector<std::string> > location_directives, std::multimap<std::string, std::vector<std::string> > server_from_config, int client_fd);
    //setters
    void    set_root(std::string root);
    void    set_accepted_request_methods(std::vector<std::string> accepted_request_methods);
    void    set_HTTP_redirection(std::string HTTP_redirection);
    void    set_autoindex(std::string autoindex);
    void    set_index_file(std::string index_file);
    //getters
    std::string &get_root();
    std::vector<std::string> &get_accepted_request_methods();
    std::string    &get_HTTP_redirection();
    std::string    &get_autoindex();
    std::string    &get_index_file();
    std::string    &get_cgi_extension();
    std::string    &get_cgi_path();
    std::string    &get_upload_directory();
};

#endif