/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webservutils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:15:12 by sbellafr          #+#    #+#             */
/*   Updated: 2024/06/12 12:16:52 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

#include "GetClass/GetClass.hpp"
#include "PostClass/PostClass.hpp"
#include "DeleteClass/DeleteClass.hpp"
#include "parsing/ParseConfig.hpp"
bool check_chunked(std::string buffer)
{
    size_t pos = buffer.find("\r\n0\r\n\r\n");
    if (pos != std::string::npos)
    {
        return true;
    }
    return false;
}

int send_http_request(int client_fd, ParseConfig &config, std::string http_request, int recv_value)
{
    std::string http_method = http_request.substr(0, 7);

    try
    {
        if (!http_method.find("GET"))
            handle_get_method(recv_value, http_request, client_fd, config);
        else if (!http_method.find("POST"))
            handle_post_method(recv_value, http_request, client_fd, config);
        else if (!http_method.find("DELETE"))
            handle_delete_method(recv_value, http_request, client_fd, config);
        else
            send_default_error_page(405, "Method Not Allowed", client_fd);
    }
    catch (const FlowControlException &e)
    {
        if (e.get_flag() == 1)
            return 1;
    }
    return 0;
}


void perfect_server()
{
    int max = 0;
    while (max < MAX_SIZE)
    {
        max++;
    }
}