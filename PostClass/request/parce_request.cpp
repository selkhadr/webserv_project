/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_request.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:35:26 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 10:35:27 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../PostClass.hpp"

void    PostClass::chuncked_request_to_unchuncked()
{
    std::string line;
    size_t      position_of_header_body_separator;
    std::string unchunked_body;

    position_of_header_body_separator = request_header.find("\r\n\r\n") + 4;
    if (position_of_header_body_separator != std::string::npos)
    {
        request_body = request_header.substr(position_of_header_body_separator);
        std::istringstream chunked_data_stream(request_body);
        while (std::getline(chunked_data_stream, line))
        {
            if (line.empty())
                continue ;
            line = line.substr(0, line.size()-1);
            std::istringstream chunk_size_stream(line);
            int chunk_size;
            if (chunk_size_stream >> std::hex >> chunk_size)
            {
                if (chunk_size == 0)
                    break ;
                chunk_size +=2;
                char *buffer = new char[chunk_size];
                chunked_data_stream.read(buffer, chunk_size);
                unchunked_body.append(buffer, chunk_size - 2);
                delete[] buffer;
            }
        }
        request_body = unchunked_body;
    }
}

void    PostClass::parce_request()
{
    size_t position_of_header_body_separator;
    size_t received_body_size;

    position_of_header_body_separator = request_header.find("\r\n\r\n") + 2;
    if (position_of_header_body_separator != std::string::npos)
    {
        received_body_size = request_header.size() - position_of_header_body_separator;
        request_body = request_header.substr(position_of_header_body_separator);
        std::map<std::string, std::string>::iterator it = request_headers.find("Transfer-Encoding");
        if (it != request_headers.end() && it->second == "chunked")
            chuncked_request_to_unchuncked();
    }
}
