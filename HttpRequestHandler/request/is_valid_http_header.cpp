/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_http_header.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:55:56 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:06:45 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"
#include "../../parsing/Server.hpp"
#include "../../parsing/Location.hpp"

void	HttpRequestHandler::find_port()
{
	std::map<std::string, std::string>::iterator it = request_headers.find("Host");
	if (it == request_headers.end())
		send_default_error_page(400, "Bad Request", client_fd);
	size_t pos = it->second.find(":");
	if (pos == std::string::npos)
		send_default_error_page(400, "Bad Request", client_fd);
	port = it->second.substr(pos + 1);
}

void	HttpRequestHandler::find_most_significant_server(ParseConfig &config)
{
	extract_request_headers();
	find_port();
	Server server(config.getserver_by_port(port, config, client_fd));
	server_from_config = server.GetServerDirectives();
	std::vector<Location> locations = server.GetLocations();
	size_t i = 0;
	while(i < locations.size())
	{
		std::map<std::string, std::vector<std::string> > location_directives = locations[i].GetLocationDirectives();
		std::string location_path = locations[i].GetPath();
		locations_as_string.insert(std::make_pair(location_path, location_directives));
		i++;
	}
}

void HttpRequestHandler::is_valid_request_header(int recv_return_value, std::string &header, int client_fd, ParseConfig &config)
{
	this->client_fd = client_fd;
	this->request_header = header;
	this->recv_return_value = recv_return_value;

	find_most_significant_server(config);
	initialize_supported_file_types();
	set_server_directives();
	is_req_well_formed();
	get_matched_location_for_request_url();
	is_location_has_redirection();
	is_method_allowed_in_location();
}
