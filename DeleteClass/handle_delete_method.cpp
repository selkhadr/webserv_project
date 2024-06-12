/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_delete_method.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:02:04 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:02:06 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DeleteClass.hpp"

void	handle_delete_method(int recv_return_value, std::string &header, int client_fd, ParseConfig &config)
{
	DeleteClass delete_class;
	delete_class.set_request_method("DELETE");
	delete_class.is_valid_request_header(recv_return_value, header, client_fd, config);
	delete_class.get_requested_resource_path();
	if (delete_class.check_path_existence() == false)
		delete_class.send_status_code_response(404, "Not Found");
	delete_class.get_resource_type();
}
