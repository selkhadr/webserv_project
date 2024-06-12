/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_server_directives.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:58:40 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:08:01 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HttpRequestHandler.hpp"

void    HttpRequestHandler::set_server_directives()
{
    if (server_from_config.empty())
        return ;
    ServerDirectives server_directives(server_from_config);

    this->server_directives = server_directives;
    
}
