/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dir_request.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:00:49 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:00:50 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../DeleteClass.hpp"

void    DeleteClass::has_required_permissions(std::string dir_path, struct stat &stat_of_dir_content)
{
    if (stat(dir_path.c_str(), &stat_of_dir_content) == -1)
        send_status_code_response(500, "Internal Server Error");
    if (access(dir_path.c_str(), READ) == -1)
        send_status_code_response(403, "Forbidden");
}

void   DeleteClass::delete_all_folder_content(std::string dir_path)
{
    std::string dir_content_path;
    std::string dir_content_name;
    struct stat stat_of_dir_content;
    DIR *dir;
    struct dirent *read_dir;

    has_required_permissions(dir_path, stat_of_dir_content);
    //closi hadi
    dir = opendir(dir_path.c_str());
    if (dir == NULL)
        send_status_code_response(500, "Internal Server Error");
    read_dir = readdir(dir);
    while (read_dir)
    {
        dir_content_name = read_dir->d_name;
        if (dir_content_name == "." || dir_content_name == "..")
        {
            read_dir = readdir(dir);
            continue ;
        }
        dir_content_path = dir_path + dir_content_name;
        has_required_permissions(dir_content_path, stat_of_dir_content);
        if (S_ISDIR(stat_of_dir_content.st_mode))
        {
            dir_content_path += "/";
            delete_all_folder_content(dir_content_path);
        }
        if (S_ISREG(stat_of_dir_content.st_mode))
        {
            if (std::remove((dir_content_path).c_str()) != 0)
                send_status_code_response(500, "Internal Server Error");
        }
        read_dir = readdir(dir);
    }
    if (closedir(dir) == -1)
        send_status_code_response(500, "Internal Server Error");
    if (std::remove((dir_path).c_str()) != 0)
        send_status_code_response(500, "Internal Server Error");
}

void DeleteClass::handle_dir_request()
{
    if (request_url_as_string.back() != '/')
        send_status_code_response(409, "Conflict");
    check_permission(READ);
    delete_all_folder_content(requested_resource_path);
    send_status_code_response(204, "No Content");
}
