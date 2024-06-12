/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_static_file.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:00:42 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:00:43 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../GetClass.hpp"

void    GetClass::handle_static_file()
{
    check_permission(READ);
    generate_response_headers();
    generate_file_content_as_response_body(requested_resource_path);
    http_response = response_status_line + response_headers + response_body;
    send_response();
}
