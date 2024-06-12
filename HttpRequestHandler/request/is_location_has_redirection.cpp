/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_location_has_redirection.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:06:26 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:06:27 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"
#include "../LocationDirectives/LocationDirectives.hpp"

void HttpRequestHandler::is_location_has_redirection()
{
    if(most_significant_location_directives.get_HTTP_redirection().empty() == false)
        send_status_code_response(301, "Moved Permanently");
}
