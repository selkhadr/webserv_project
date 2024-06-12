/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:20:58 by sbellafr          #+#    #+#             */
/*   Updated: 2024/06/09 19:10:19 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"Request.hpp"

Request::Request(/* args */)
{
}

Request::~Request()
{
}
int Request::RequestName(std::string request)
{
	if(request.substr(0, request.find(" ")) == "POST")
		return (1);
	else if(request.substr(0, request.find(" ")) == "GET")
		return (2);
	else if(request.substr(0, request.find(" ")) == "DELETE")
		return (3);
	else
		return (0);
	return (0);
}
int Request::find_header_end(const std::string &buffer)
{
	size_t pos = buffer.find("\r\n\r\n");
	if (pos != std::string::npos)
	{
		return static_cast<int>(pos + 4);
	}
	return -1;
}

// Function to copy content from buffer to file



int Request::calculate_content_length(std::string buffer)
{
	std::istringstream httpRequestStream(buffer);
	std::string line;
	int contentLength = -1;
	while (std::getline(httpRequestStream, line))
	{
		if (line.find("Content-Length:") != std::string::npos)
		{
			if (line[line.length() - 1] == '\r')
				line.pop_back();
			std::istringstream lineStream(line);
			std::string header;
			lineStream >> header >> contentLength;
			break;
		}
	}
	return contentLength;
}
int Request::server_choice(std::vector<webserv> server, int size, int i)
{
	for (int j = 0; j < size; j++)
	{
		if (server[j].get_ser_fd() == i)
		{
			return j;
		}
	}
	return -1;
}