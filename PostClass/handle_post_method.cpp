/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_post_method.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:23:47 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:23:48 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PostClass.hpp"

void    PostClass::execute_post_processing()
{
    std::string cgi_extension = most_significant_location_directives.get_cgi_extension();

    if (if_location_has_cgi())
    {
        if (check_path_existence() == false)
		    send_status_code_response(404, "Not Found");
	    get_resource_type();
    }
    else
        upload_manually();
}

void    handle_post_method(int recv_return_value, std::string header, int client_fd, ParseConfig &config)
{
    PostClass   post_class;
    post_class.set_request_method("POST");
    post_class.is_valid_request_header(recv_return_value, header, client_fd, config);

    post_class.parce_request();
    post_class.get_requested_resource_path();
    post_class.execute_post_processing();
}
