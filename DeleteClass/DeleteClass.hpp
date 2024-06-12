/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:01:56 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:01:57 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETECLASS_HPP
#define DELETECLASS_HPP

#include "../HttpRequestHandler/HttpRequestHandler.hpp"

class   DeleteClass:public HttpRequestHandler
{
public:
    //is_delete_req_well_formed file
    void    handle_file_type();
    void    handle_static_file();
    void    handle_dir_request();
    void    delete_all_folder_content(std::string dir_path);
    void    has_required_permissions(std::string dir_path, struct stat &stat_of_dir_content);
};

//handle_delete_method file
void	handle_delete_method(int recv_return_value, std::string &header, int client_fd, ParseConfig &config);
#endif