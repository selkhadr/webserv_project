/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseConfig.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:35:48 by nel-mous          #+#    #+#             */
/*   Updated: 2024/06/12 11:47:29 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSECONFIG
#define PARSECONFIG

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include "Server.hpp"
#include "Location.hpp"

class ParseConfig 
{
    private:
        int open_location_count;
        int close_location_count;
        std::vector<Server> m_servers;
        std::vector<Location> _locations;
        static std::vector<std::string> _AllowedDirectives;
        static bool hostNameFound;
        
    public:
        ParseConfig();
        ~ParseConfig();
        std::vector<Server> GetServers() const;
        int readfile(const std::string &filename);
        void initialize_allowed_directives();
        /*****/
		bool is_directive_allowed(const std::string& directive);
        int  check_directive(const std::vector<Server>& Servers, const std::vector<Location> &Locations);
        bool is_value_valid(const std::string& key, const std::string& value, const std::vector<std::string>& values);
        bool emptyline(const std::string& str);
        bool handle_errors(const std::string& errorMessage);
        int  check_directives_size(std::string key, std::vector<std::string> values, int check);
        int check_essential_directives(std::vector<std::string> keys);
        bool special_character(const std::string& value);

        /*****/
        int parse_server_block(std::ifstream& Confile, Server& server, std::string &line);
        int process_server_block(std::ifstream &Confile, Server &server, std::string &line, bool &serverNameFound, int &counter);
        int line_in_server_block(std::string& line, Server &server,  std::vector<std::string> &keys, bool &serverNameFound, bool &ServerError);
        bool is_server(const std::string &line);
        /****/
        int parse_location_block(std::ifstream& Confile,  Server& server, std::string &line);
        int process_location_block(std::ifstream& Confile, Server& server, Location& location, std::string& line);
        int line_in_location_block(std::string& line, Location& location, bool& LocationError, bool& prevLocationClosed, bool inLocation);
        bool is_location_directive(const std::string& line);
        /******/
        
        bool is_integer(const std::string& str);
        bool is_valid_ip_address(const std::string& str);
        bool is_port_valid(const std::string& str);
        int  has_semicolon(std::string &line);
        int  semicolon_in_location(std::string &line);
        bool closed_brace(const std::string &line);
        bool opened_brace(const std::string &line);
        int check_braces_balance();
        bool is_comment(const std::string &line);
        std::string remove_comment(const std::string& line);
        // /****/
        bool check_directive_in_location(std::string &directive);
        bool check_directive_in_server(std::string &directive);
        Server getserver_by_port(std::string port_value, ParseConfig &Config, int client_fd);
        std::vector<std::string>  getValues(std::vector<std::string> &ports) const;
        std::vector<std::string>  getHosts(std::vector<std::string> &ports) const;
        void default_port(Server &server);
        
};

#endif