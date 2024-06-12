/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_type.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:00:58 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:00:59 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../DeleteClass.hpp"

void   DeleteClass::handle_static_file()
{
    if (std::remove(requested_resource_path.c_str()) != 0)
        send_status_code_response(500, "Internal Server Error");
    else
        send_status_code_response(204, "No Content");
}

void    DeleteClass::handle_file_type()
{
   handle_static_file();
}
