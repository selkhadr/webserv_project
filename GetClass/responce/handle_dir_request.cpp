/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dir_request.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:00:37 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:00:38 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../GetClass.hpp"

void    GetClass::get_auto_index()
{
    if(most_significant_location_directives.get_autoindex() == "off")
        send_status_code_response(403, "Forbidden");
    else
    {
        generate_response_status_line(200, "Ok");
        response_headers = "Content-Type: text/html\r\n";
        response_content_length = directory_content_list.size();
        response_headers += "Content-Length: " + integer_to_string(response_content_length) + "\r\n\r\n";
        response_body = directory_content_list;
        http_response = response_status_line + response_headers + response_body;
        send_response();
    }
}

void GetClass::handle_dir_request()
{
    std::string index_file_path;

    if (request_url_as_string.back() != '/')
    {
        most_significant_location_directives.set_HTTP_redirection(request_url_as_string + "/");
        send_status_code_response(301, "Moved Permanently");
    }
    check_permission(READ);
    if (is_dir_has_index_file() == true)
    {
        if (stat(requested_resource_path.c_str(), &stat_of_request_resource) == -1)
            send_status_code_response(500, "Internal Server Error");
        handle_file_type();
    }
    else
        get_auto_index();
}
