/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dir_request.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:55:59 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:05:51 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

bool    HttpRequestHandler::is_dir_has_index_file()
{
    std::string index_file = most_significant_location_directives.get_index_file();

    int is_index_file_exist = 0;
    dir = opendir(requested_resource_path.c_str());
    if (!dir){
        send_status_code_response(500, "Internal Server Error");
        throw std::runtime_error(std::strerror(errno)); 
    }
    read_dir = readdir(dir);
    while (read_dir)
    {
        directory_content_list += read_dir->d_name;
        directory_content_list += " \n";
        if (read_dir->d_name == index_file)
            is_index_file_exist = 1;
        read_dir = readdir(dir);
    }
    if (closedir(dir) == -1)
        send_status_code_response(500, "Internal Server Error");
    if(!is_index_file_exist)
        return false;
    requested_resource_path += index_file;
    return true;
}
