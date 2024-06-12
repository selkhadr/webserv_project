/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_response_file.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:00:15 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:09:44 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

void HttpRequestHandler::generate_file_content_as_response_body(std::string requested_resource_path)
{
    if (response_content_length)
        file_content_to_string(requested_resource_path, response_body);
}

void HttpRequestHandler::send_response()
{
    ssize_t bytes_sent = send(client_fd, http_response.c_str(), http_response.size(), 0);
    while (bytes_sent < static_cast<ssize_t>(http_response.size()))
    {
        if (bytes_sent == -1)
            send_status_code_response(500, "Internal Server Error");
        if (bytes_sent == 0)
            break ;
        http_response = http_response.substr(bytes_sent);
        bytes_sent = send(client_fd, http_response.c_str(), http_response.size(), 0);
    }
    if (close(client_fd) == -1)
        send_status_code_response(500, "Internal Server Error");
    throw (FlowControlException(0));
}
