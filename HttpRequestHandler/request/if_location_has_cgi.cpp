/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_location_has_cgi.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:55:45 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:06:23 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

int is_standard_CGI_environment_variable(const std::string &key)
{
    if (key == "CONTENT_LENGTH" || key == "CONTENT_TYPE" || key == "REQUEST_METHOD" || key == "PATH_INFO" || key == "QUERY_STRING" || key == "SCRIPT_FILENAME" || key == "REDIRECT_STATUS" || key == "SCRIPT_NAME" || key == "SERVER_NAME" || key == "SERVER_PROTOCOL")
        return 1;
    return 0;
}

void    HttpRequestHandler::add_standard_CGI_environment_variable()
{
    std::map<std::string, std::string>::iterator it = request_headers.find("Content-Length");
    if (it != request_headers.end())
        envp_as_vec.push_back("CONTENT_LENGTH=" + it->second);
    it = request_headers.find("Content-Type");
    if (it != request_headers.end())
        envp_as_vec.push_back("CONTENT_TYPE=" + it->second);
    envp_as_vec.push_back("SCRIPT_FILENAME=" + requested_resource_path);
    envp_as_vec.push_back("SCRIPT_NAME=" +  request_url_as_vector.back());
    envp_as_vec.push_back("QUERY_STRING=");
    envp_as_vec.push_back("REQUEST_METHOD=" + request_method);
    envp_as_vec.push_back("REDIRECT_STATUS=200");
    envp_as_vec.push_back("SERVER_NAME=webserv");
    envp_as_vec.push_back("SERVER_PROTOCOL=HTTP/1.1");
}

void    HttpRequestHandler::format_keys()
{
    std::string key;

    std::map<std::string, std::string>::iterator it = request_headers.begin();
    while(it != request_headers.end())
    {
        key = it->first;
        std::replace(key.begin(), key.end(), '-', '_');
        convert_to_uppercase(key);
        if (!is_standard_CGI_environment_variable(key))
            key = "HTTP_" + key;
        envp_as_vec.push_back(key + "=" + it->second);
        key.clear();
        it++;
    }
    add_standard_CGI_environment_variable();
}

void    HttpRequestHandler::env_variables_from_req_headers()
{
    format_keys();
    envp = copy_vector_to_cstring_array(envp_as_vec, client_fd);
}

void HttpRequestHandler::fill_argc()
{
    std::string cgi_path =  most_significant_location_directives.get_cgi_path();

    argc = new char* [3];
    argc[0] = new char[cgi_path.size() + 1];
    strcpy(argc[0], cgi_path.c_str());
    argc[1] = new char[requested_resource_path.size() + 1];
    strcpy(argc[1], requested_resource_path.c_str());
    argc[2] = NULL;
}

int HttpRequestHandler::generate_data_for_post()
{
    std::string temp_file_path = "/tmp/post_body.tmp";
    int temp_file_fd;
    int fd;

    temp_file_fd = open(temp_file_path.c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (temp_file_fd == -1)
        send_status_code_response(500, "Internal Server Error");
    ssize_t bytes_written = write(temp_file_fd, request_body.c_str(), request_body.size());
    if (bytes_written != static_cast<ssize_t>(request_body.size())){
        close(temp_file_fd);
        send_status_code_response(500, "Internal Server Error");
    }
    close(temp_file_fd);
    fd = open(temp_file_path.c_str(), O_RDONLY);
    if (fd == -1) {
        send_status_code_response(500, "Internal Server Error");
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        close(fd);
        send_status_code_response(500, "Internal Server Error");
    }
    close(fd);
    return 0;
}

void    HttpRequestHandler::handle_file_type()
{
    std::string cgi_extension = most_significant_location_directives.get_cgi_extension();

    if (if_location_has_cgi() && requested_resource_path.find(cgi_extension) != std::string::npos)
        prepare_and_execute_cgi();
    else
        handle_static_file();
}
