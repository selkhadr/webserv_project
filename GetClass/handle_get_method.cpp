/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_get_method.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:58:16 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 12:15:18 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetClass.hpp"

void	handle_get_method(int recv_return_value, std::string &header, int client_fd, ParseConfig &config)
{
	GetClass get_class;

	get_class.set_request_method("GET");
	get_class.is_valid_request_header(recv_return_value, header, client_fd, config);
	get_class.get_requested_resource_path();
	if (get_class.check_path_existence() == false)
		get_class.send_status_code_response(404, "Not Found");

	get_class.get_resource_type();
}
