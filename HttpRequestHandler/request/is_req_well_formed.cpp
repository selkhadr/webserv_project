/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_req_well_formed.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:06:36 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:06:37 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

void    HttpRequestHandler::is_req_well_formed()
{
    extract_request_url_as_string_from_header();
    if(request_url_as_string.size() > 2048)
        send_status_code_response(414, "Request-URL Too long");
    url_contain_allowed_characters();
}
