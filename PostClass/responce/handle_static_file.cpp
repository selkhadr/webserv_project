/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_static_file.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:23:13 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:23:14 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../PostClass.hpp"

void    PostClass::handle_file_type()
{
    std::string cgi_extension = most_significant_location_directives.get_cgi_extension();

    if (requested_resource_path.find(cgi_extension) != std::string::npos)
        prepare_and_execute_cgi();
    else
        send_status_code_response(403, "forbidden");
}
