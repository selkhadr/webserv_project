/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_default_error_page.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:07:30 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:07:31 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../HttpRequestHandler.hpp"

void    send_default_error_page(int response_status_code, std::string response_reason_phrase, int client_fd)
{
    struct stat stat_of_default_error_page;
    std::string default_error_page = "./error_pages/default_error_page.html";
    std::string status_line = "HTTP/1.1 "+ integer_to_string(response_status_code) + " " + response_reason_phrase + "\r\n";
    std::string response_headers = "Content-Type: text/html\r\n";
    size_t      content_lenght = 0;
    std::string response_body;
    std::string response;

    if (stat(default_error_page.c_str(), &stat_of_default_error_page) != -1)
        content_lenght = stat_of_default_error_page.st_size;
    else
        throw (FlowControlException(0));
    response_headers += "Content-Length: " + integer_to_string(content_lenght) + "\r\n\r\n";
    if (content_lenght)
        file_content_to_string(default_error_page, response_body);
    response = status_line + response_headers + response_body;
    send(client_fd, response.c_str(), response.size(), 0);
    close(client_fd);
    throw (FlowControlException(0));
}
