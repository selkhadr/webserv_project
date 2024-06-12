/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_method_allowed_in_location.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:06:32 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:06:33 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

void HttpRequestHandler::is_method_allowed_in_location()
{
    std::vector<std::string>    accepted_request_methods = most_significant_location_directives.get_accepted_request_methods();
    if (std::find(accepted_request_methods.begin(), accepted_request_methods.end(), request_method) != accepted_request_methods.end())
        return ;
    send_status_code_response(405, "Method not allowed");
}
