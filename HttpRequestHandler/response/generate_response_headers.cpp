/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_response_headers.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:05:01 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:09:29 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

void HttpRequestHandler::check_permission(Permission permission)
{
    if (access(requested_resource_path.c_str(), permission) == -1)
        send_status_code_response(403, "Forbidden");
}

void    HttpRequestHandler::initialize_supported_file_types()
{
    file_types.insert(std::make_pair(".txt", "text/plain"));
    file_types.insert(std::make_pair(".html", "text/html"));
    file_types.insert(std::make_pair(".xml", "application/xml"));
    file_types.insert(std::make_pair(".json", "application/json"));
    file_types.insert(std::make_pair(".jpg", "image/jpeg"));
    file_types.insert(std::make_pair(".png", "image/png"));
    file_types.insert(std::make_pair(".gif", "image/gif"));
    file_types.insert(std::make_pair(".mp3", "audio/mpeg"));
    file_types.insert(std::make_pair(".MP4", "video/mp4"));
    file_types.insert(std::make_pair(".ogg", "audio/ogg"));
}

void    HttpRequestHandler::determine_content_type()
{
    size_t index = requested_resource_path.find(".", 1);
    if (index != std::string::npos)
    {
        requested_file_extension = requested_resource_path.substr(index);
        if (file_types.find(requested_file_extension) != file_types.end())
            response_content_type = file_types[requested_file_extension];
        else
            response_content_type = "application/octet-stream";
    }
    else
        response_content_type = "application/octet-stream";
}

void    HttpRequestHandler::generate_response_headers()
{
    generate_response_status_line(200, "Ok");
    response_content_length = stat_of_request_resource.st_size;
    determine_content_type();
    response_headers += "Content-Length: " + integer_to_string(response_content_length) + "\r\n";
    response_headers += "Content-Type: " + response_content_type + "\r\n\r\n";
}
