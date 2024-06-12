/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_manually.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:23:43 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:23:44 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../PostClass.hpp"

void    PostClass::handle_static_file()
{

}

void   PostClass::extract_boundary()
{
    std::map<std::string, std::string>::iterator it = request_headers.find("Content-Type");
    size_t  index;

    if (it != request_headers.end())
    {
        index = it->second.find("boundary=");
        if (index != std::string::npos)
            boundary = it->second.substr(index + std::strlen("boundary="));
    }
    boundary = "--" + boundary;
}

void    PostClass::extract_file_name()
{
    size_t  start = request_body.find("Content-Disposition:");
    if (start == std::string::npos)
        send_status_code_response(400, "Bad Request");

    size_t  end = request_body.find("\r\n", start);
    if (end == std::string::npos)
        send_status_code_response(400, "Bad Request");
    std::string content_disposition = request_body.substr(start, end - start);
    start = content_disposition.find("filename=");
    if (start == std::string::npos)
        send_status_code_response(400, "Bad Request");
    start = start + std::strlen("filename=") + 1;
    end = content_disposition.find("\"", start);
    if (end == std::string::npos)
        send_status_code_response(400, "Bad Request");
    file_name = content_disposition.substr(start, end - start);
}

void PostClass::extract_file_content()
{
    size_t  start_of_the_file_content;
    size_t  end_of_the_file_content;
    std::string blank_line = "\r\n\r\n";

    start_of_the_file_content = request_body.find(blank_line) + blank_line.size();
    if (start_of_the_file_content != std::string::npos)
    {
        end_of_the_file_content = request_body.find(boundary, start_of_the_file_content);
        if (end_of_the_file_content != std::string::npos)
           file_content = request_body.substr(start_of_the_file_content, end_of_the_file_content - start_of_the_file_content);
        else
            send_status_code_response(500, "Internal Server Error");
    }
}

void    PostClass::create_and_populate_file()
{
    if (file_name.empty() == false)
    {
        std::string path;
        std::string upload_dir = most_significant_location_directives.get_upload_directory();
        if (stat(upload_dir.c_str(), &stat_of_upload) == -1)
            send_status_code_response(500, "Internal Server Error");
        if (stat_of_upload.st_mode & S_IFDIR)
        {
            if (upload_dir.back() == '/')
                path = upload_dir + file_name;
            else
                path = upload_dir + "/" + file_name;
        }
        else if (stat_of_upload.st_mode & S_IFREG)
            send_status_code_response(500, "Internal Server Error");
        std::ofstream created_file(path);
        if (!created_file)
            send_status_code_response(500, "Internal Server Error");
        created_file << file_content;
        created_file.close();
    }
    else
        send_status_code_response(400, "Bad Request: Filename is missing");
}

void    PostClass::upload_manually()
{
    extract_boundary();
    size_t start = request_body.find(boundary);
    while (start != std::string::npos)
    {
        extract_file_name();
        extract_file_content();
        create_and_populate_file();
        start = request_body.find(boundary, start + boundary.size());
        if (start == std::string::npos)
            break ;
        if (start == request_body.find(boundary + "--"))
            break ;
        request_body = request_body.substr(start);
        start = request_body.find(boundary);
    }
    send_status_code_response(201, "Created");
}
