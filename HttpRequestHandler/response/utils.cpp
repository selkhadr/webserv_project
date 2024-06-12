/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:10:25 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:10:26 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

int file_content_to_string(std::string file_name, std::string &response_body)
{
    std::ifstream file(file_name);
    std::stringstream buffer;

    buffer << file.rdbuf();
    response_body = buffer.str();
    return 0;
}

std::string integer_to_string(int num)
{
    std::stringstream ss;
    ss << num;
    return (ss.str());
}
