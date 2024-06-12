/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matched_location_for_request_url.cpp           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:05:35 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:05:36 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

void	HttpRequestHandler::build_request_url_as_vectors()
{
	std::string			tmp;
	std::istringstream stream_string(request_url_as_string);

	getline(stream_string, tmp, '/');
	while(getline(stream_string, tmp, '/'))
		request_url_as_vector.push_back(tmp);
}

void	HttpRequestHandler::build_locations_as_vector()
{
	std::string													directory;
	std::vector<std::string>									nested_vector;
	std::map<std::string, std::map<std::string, std::vector<std::string> > >::iterator	it = locations_as_string.begin();

	std::istringstream	string_stream;
	while(it != locations_as_string.end())
	{
		string_stream.clear();
		string_stream.str(it->first);
		getline(string_stream, directory, '/');
		while (getline(string_stream, directory, '/'))
			nested_vector.push_back(directory);
		locations_as_vectors.push_back(nested_vector);
		nested_vector.clear();
		it++;
	}
}

void   HttpRequestHandler::get_matched_location_for_request_url()
{
    build_locations_as_vector();
	build_request_url_as_vectors();
	most_significant_location_as_string = find_most_significant_location(request_url_as_vector, locations_as_vectors);
    if (most_significant_location_as_string == "/")
    {
        std::map<std::string, std::map<std::string, std::vector<std::string> > >::iterator it = locations_as_string.find("/");
        if (it == locations_as_string.end() && it->first.size() == 1)
			send_default_error_page(404, "Not Found", client_fd);
    }
    set_most_significant_location_directives();
}
