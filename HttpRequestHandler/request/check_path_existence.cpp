/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_existence.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:01:11 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:04:53 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

bool HttpRequestHandler::check_path_existence()
{
    return (stat(requested_resource_path.c_str(), &stat_of_request_resource) == 0);
}
