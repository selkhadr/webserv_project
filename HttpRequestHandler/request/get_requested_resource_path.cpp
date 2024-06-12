/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_requested_resource_path.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:05:38 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:05:39 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

void	HttpRequestHandler::build_requested_resource_path()
{
	requested_resource_path = most_significant_location_directives.get_root() + "/" + requested_resource_from_url;
}

void	HttpRequestHandler::extract_requested_resource_from_url()
{
	requested_resource_from_url = request_url_as_string.substr(most_significant_location_as_string.size());
}

void	HttpRequestHandler::get_requested_resource_path()
{
	extract_requested_resource_from_url();
	build_requested_resource_path();
}
