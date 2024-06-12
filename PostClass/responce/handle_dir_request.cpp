/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dir_request.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:23:08 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:23:09 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../PostClass.hpp"

void PostClass::handle_dir_request()
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
        send_status_code_response(403, "Forbidden");
}
