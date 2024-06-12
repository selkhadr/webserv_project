/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_status_code_response.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:10:16 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:10:17 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

int HttpRequestHandler::generate_response_status_line(int response_status_code, std::string response_reason_phrase)
{
    this->response_status_code = response_status_code;
    this->response_reason_phrase = response_reason_phrase;
    response_status_line = integer_to_string(response_status_code);

    response_status_line = http_version + " " + response_status_line + " " + response_reason_phrase + "\r\n";
    return 0;
}

int HttpRequestHandler::generate_body_from_default_error_page()
{
    if (stat(server_directives.get_default_error_page().c_str(), &stat_of_error_page) != -1)
    {
        response_selected_error_page = server_directives.get_default_error_page();
        response_content_length = stat_of_error_page.st_size;
    }
    return 0;
}

int HttpRequestHandler::generate_status_code_headers(int is_redirection_response)
{
    std::map<int, std::string> error_pages = server_directives.get_error_pages();

    if (is_redirection_response)
    {
        response_headers = "Location: " + most_significant_location_directives.get_HTTP_redirection() + "\r\n";
        response_headers += "Content-Length: 0\r\n\r\n";
        return 0;
    }
    response_headers += "Content-Type: text/html\r\n";
    if (error_pages.find(response_status_code) != error_pages.end())
    {
        if (stat(error_pages[response_status_code].c_str(), &stat_of_error_page) != -1)
        {
            response_selected_error_page = error_pages[response_status_code];
            response_content_length = stat_of_error_page.st_size;
        }
        else
            generate_body_from_default_error_page();
    }
    else
        generate_body_from_default_error_page();
    response_headers += "Content-Length: " + integer_to_string(response_content_length) + "\r\n\r\n";
    return 0;
}

void HttpRequestHandler::send_status_code_response(int response_status_code, std::string response_reason_phrase)
{
    generate_response_status_line(response_status_code, response_reason_phrase);
    if (response_status_code / 100 == 3)
        generate_status_code_headers(1);
    else
    {
        generate_status_code_headers(0);
        generate_file_content_as_response_body(response_selected_error_page);
    }
    http_response = response_status_line + response_headers + response_body;
    send_response();
}
