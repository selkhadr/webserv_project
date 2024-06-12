/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_post_req_well_formed.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:58:48 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:22:27 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../PostClass.hpp"

void    PostClass::check_content_length()
{
    double body_max_size = server_directives.get_body_max_size();
    if (request_headers.find("Transfer-Encoding") != request_headers.end() && request_headers["Transfer-Encoding"] != "chunked")
        send_default_error_page(501, "Not implemented", client_fd);
    else if (request_headers.find("Transfer-Encoding") == request_headers.end())
    {
        if (request_headers.find("Content-Length") == request_headers.end())
            send_default_error_page(400, "Bcad request", client_fd);
        else
        {
            content_length = atoi(request_headers["Content-Length"].c_str());
            if (content_length > body_max_size)
                send_default_error_page(413, "Request entity too large", client_fd);
            else if (!content_length)
                send_default_error_page(400, "bad Request", client_fd);
        }
    }
}

void    PostClass::is_req_well_formed()
{
    extract_request_url_as_string_from_header();
    if (request_url_as_string.size() > 2048)
        send_default_error_page(414, "Request-URL Too long", client_fd);
    url_contain_allowed_characters();
    check_content_length();
}
