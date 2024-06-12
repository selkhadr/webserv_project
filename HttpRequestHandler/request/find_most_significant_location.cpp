/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_most_significant_location.cpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:05:31 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:05:32 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

void HttpRequestHandler::find_semilare_locations_to_url(std::vector<std::string> &request_url_as_vector, std::vector<std::vector<std::string> > &local_locations_as_vectors)
{
	size_t i = 0;
	size_t j = 0;

	while(i < local_locations_as_vectors.size())
	{
		j = 0;
		if (local_locations_as_vectors[i].size() > request_url_as_vector.size())
		{
			local_locations_as_vectors.erase(local_locations_as_vectors.begin() + i);
			continue;
		}
		while(j < request_url_as_vector.size())
		{
			if (i < local_locations_as_vectors.size() && j < local_locations_as_vectors[i].size() && request_url_as_vector[j] != local_locations_as_vectors[i][j])
			{
				local_locations_as_vectors.erase(local_locations_as_vectors.begin() + i);
				i--;
				break;
			}
			j++;
		}
		i++;
	}
}

std::string HttpRequestHandler::vector_to_string(std::vector<std::string>&locations_as_vectors)
{
	std::string string;

	size_t i = 1;
	string = "/";
	if (locations_as_vectors.size())
		string += locations_as_vectors[0];
	while (i < locations_as_vectors.size())
	{
		string += "/";
		string += locations_as_vectors[i];
		i++;
	}
	return string;
}

std::string HttpRequestHandler::find_most_significant_location(std::vector<std::string> &request_url_as_vector, std::vector<std::vector<std::string> > local_locations_as_vectors)
{
	size_t i = 0;
	size_t most_significant_by_size;
	std::vector<std::string> copy_of_most_significant_vector;

	find_semilare_locations_to_url(request_url_as_vector, local_locations_as_vectors);
	if(local_locations_as_vectors.size() == 0)
		return ("/");
	else if (local_locations_as_vectors.size() == 1)
		return vector_to_string(local_locations_as_vectors[0]);
	most_significant_by_size = local_locations_as_vectors[0].size();
	copy_of_most_significant_vector = local_locations_as_vectors[0];
	while(i < local_locations_as_vectors.size())
	{
		if (local_locations_as_vectors[i].size() > most_significant_by_size)
		{
			copy_of_most_significant_vector = local_locations_as_vectors[i];
			most_significant_by_size = local_locations_as_vectors[i].size();
		}
		i++;
	}
	return vector_to_string(copy_of_most_significant_vector);
}