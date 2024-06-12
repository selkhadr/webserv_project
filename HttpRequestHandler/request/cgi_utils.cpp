/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_utils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:04:23 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:04:25 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

bool    HttpRequestHandler::if_location_has_cgi()
{
    std::string cgi_extension = most_significant_location_directives.get_cgi_extension();
    std::string cgi_path = most_significant_location_directives.get_cgi_path();

    if (!cgi_extension.empty() && !cgi_path.empty())
        return true;
    return false;
}

void    convert_to_uppercase(std::string &key)
{
    std::string::iterator it = key.begin();

    while(it != key.end())
    {
        *it = std::toupper(static_cast<unsigned char>(*it));
        it++;
    }
}

char **copy_vector_to_cstring_array(std::vector<std::string> &vect, int client_fd)
{
    char **envp = NULL;
    int i = 0;

    try
    {
        envp = new char*[vect.size() + 1];
        while (i < static_cast<int>(vect.size()))
        {
            envp[i] = new char[vect[i].size() + 1];
            strcpy(envp[i], vect[i].c_str());
            i++;
        }
        envp[i] = NULL;
    }
    catch (std::bad_alloc& ba)
    {
        send_default_error_page(500, "internal Server Eroor", client_fd);
    }
    return envp;
}

std::string extract_content_type(const std::string& cgi_output)
{
    std::string content_type;
    size_t begin_of_line = cgi_output.find("Content-type: ");
    size_t end_of_line;
    size_t string_lenght = strlen("Content-Type: ");

    if (begin_of_line != std::string::npos)
    {
        end_of_line = cgi_output.find("\n", begin_of_line);
        if (end_of_line != std::string::npos)
            return (cgi_output.substr(begin_of_line + string_lenght, end_of_line - string_lenght));
    }
    return ("text/plain");
}
