/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_request.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:05:02 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:05:03 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

void    HttpRequestHandler::extract_request_url_as_string_from_header()
{
    std::string request_line;
	request_line = request_header.substr(0, request_header.find("\r\n"));
	std::istringstream 	request_line_as_stream(request_line);

	getline(request_line_as_stream, request_method,' ');
	getline(request_line_as_stream, request_url_as_string, ' ');
	getline(request_line_as_stream, http_version, ' ');
    if (http_version != "HTTP/1.1")
        send_default_error_page(505, "HTTP Version Not Supported", client_fd);
}

bool    HttpRequestHandler::allowed_speciel_character(char c)
{
    if (c != '-' && c != '.' && c != '_' && c != '~' && c != ':' && c != '/' && c != '?' && c != '#'
    && c != '[' && c != ']' && c != '!' && c != '$' && c != '*' && c != ')' && c != '(' && c != '\''
    && c != '+' && c != ',' && c != ';' && c != '=' && c != '%' && c != '@')
        send_default_error_page(400, "Bad Request", client_fd);
    return true;
}

void HttpRequestHandler::url_contain_allowed_characters()
{
    std::string::iterator it = request_url_as_string.begin();
    while (it != request_url_as_string.end())
    {
        if (!std::isalnum(*it) && !allowed_speciel_character(*it))
            send_default_error_page(400, "Bad Request", client_fd);
        it++;
    }
}
