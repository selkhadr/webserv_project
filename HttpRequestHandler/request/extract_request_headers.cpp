/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_request_headers.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:05:05 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:05:06 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

void    HttpRequestHandler::extract_request_headers()
{
	std::string        line;
    std::istringstream request_header_as_stream(request_header);
    int                 end_of_key;
    int                 end_of_value;

    getline(request_header_as_stream, line);
    while (getline(request_header_as_stream, line) && line.size() > 2)
    {
        end_of_key = line.find(": ") + 2;
        end_of_value = line.size() - end_of_key - 1;
        request_headers.insert(std::make_pair(line.substr(0, end_of_key - 2), line.substr(end_of_key , end_of_value)));
    }
}
  