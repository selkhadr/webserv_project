/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_and_execute_cgi.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:06:54 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:06:55 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

void    HttpRequestHandler::read_cgi_output_pipe()
{
    char buffer[5000];
    ssize_t returned_bytes;

    while ((returned_bytes = read(cgi_output_pipe[0], buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[returned_bytes] = 0;
        cgi_output += buffer;
    }
    if (returned_bytes == -1)
        send_status_code_response(500, "Internal Server Error");
    if (close(cgi_output_pipe[0]) == -1)
        send_status_code_response(500, "Internal Server Error");
}

void    HttpRequestHandler::generate_cgi_headers()
{
    response_content_type = extract_content_type(cgi_output_headers);
    response_content_length = cgi_output_body.size();
    response_headers += "Content-Length: " + integer_to_string(response_content_length) + "\r\n";
    response_headers += "Content-Type: " + response_content_type + "\r\n\r\n";
}

void HttpRequestHandler::generate_cgi_output_response()
{
    generate_response_status_line(200, "Ok");
    generate_cgi_headers();
    http_response = response_status_line + response_headers + cgi_output_body;
}

void    HttpRequestHandler::parse_cgi_output()
{
    std::istringstream cgi_output_stream(cgi_output);
    std::string line;
    bool blank_line_existance = false;

    while (getline(cgi_output_stream, line))
    {
        line += "\n";
        if (line == "\r" || line == "\r\n" || line == "\n")
        {
            blank_line_existance = true ;
            continue ;
        }
        if (blank_line_existance)
            cgi_output_body += line;
        else
            cgi_output_headers += line;
    }
}

void    HttpRequestHandler::send_cgi_output_response()
{
    parse_cgi_output();
    generate_cgi_output_response();
    send_response();
}

int    HttpRequestHandler::execute_cgi_script()
{
    double execution_time_limit = server_directives.get_execution_time_limit();
    if (pipe(cgi_output_pipe) == -1)
        send_status_code_response(500, "Internal Server Error");
    start_time = clock();
    pid = fork();
    if (pid == 0)
    {
        if (close (cgi_output_pipe[0]) == -1)
            return (1);
        if (request_method == "POST")
        {
            if (generate_data_for_post())
                return 1;
        }
        if (dup2(cgi_output_pipe[1], STDOUT_FILENO) == -1)
            return (1);
        if (dup2(cgi_output_pipe[1], STDERR_FILENO) == -1)
            return (1);
        if (close(cgi_output_pipe[1]) == -1) 
            return (1);
        if (execve(argc[0], argc, envp) == -1)
            return (1);
    }
    if (pid != 0)
    {
        if (close(cgi_output_pipe[1]) == -1) 
            send_status_code_response(500, "Internal Server Error");
        while (true)
        {
            waitpid_result = waitpid(pid, &waitpid_status, WNOHANG);
            if (waitpid_result == -1)
                send_status_code_response(500, "Internal Server Error");
            else if (waitpid_result)
                break;
            end_time = clock();
            execution_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            if (execution_time > execution_time_limit)
            {
                if (kill(pid, SIGTERM) == -1)
                    send_status_code_response(500, "Internal Server Error");
                send_status_code_response(504, "Gateway Timeout");
            }
        }
        if (WIFEXITED(waitpid_status))
        {
            int child_return_value = WEXITSTATUS(waitpid_status);
            if (child_return_value == 1)
                send_status_code_response(500, "Internal Server Error");
        }
        read_cgi_output_pipe();
        send_cgi_output_response();
    }
    else
        send_status_code_response(500, "Internal Server Error");
    return 0;
}


int HttpRequestHandler::prepare_and_execute_cgi()
{
    check_permission(EXECUTE);
    env_variables_from_req_headers();
    fill_argc();
    if (execute_cgi_script())
        throw(FlowControlException(1));
    return 0;
}
