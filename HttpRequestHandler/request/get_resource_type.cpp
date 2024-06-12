/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_resource_type.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:55:52 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:08:08 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

void HttpRequestHandler::get_resource_type()
{
    if (stat_of_request_resource.st_mode & S_IFDIR)
        handle_dir_request();
    else if (stat_of_request_resource.st_mode & S_IFREG)
        handle_file_type();
    else
        send_status_code_response(404, "Not Found");
}
