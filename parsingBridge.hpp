/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingBridge.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:12:01 by sbellafr          #+#    #+#             */
/*   Updated: 2024/06/11 16:31:44 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSINGBRIDGE_HPP
#define PARSINGBRIDGE_HPP
#include "webserv.hpp"
#include "parsing/ParseConfig.hpp"
class webserv;
class parsingBridge
{
private:
    char **av;
    ParseConfig Config;
    std::vector<webserv> server;

public:
     std::vector<webserv> serverConfiger(/* args */);
    parsingBridge(char **av,  ParseConfig Config);
    ~parsingBridge();
};

#endif