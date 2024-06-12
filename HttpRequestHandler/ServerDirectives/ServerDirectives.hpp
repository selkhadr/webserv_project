/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerDirectives.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:31:36 by selkhadr          #+#    #+#             */
/*   Updated: 2024/04/26 16:31:37 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERDIRECTIVES_HPP
#define SERVERDIRECTIVES_HPP

#include <map>
#include <string>
#include <iostream>
#include <iostream>
#include <vector>

class   ServerDirectives
{
private:
    std::map<int, std::string>  error_pages;
    std::string                 default_error_page;
    double                 execution_time_limit;
    double                 body_max_size;
public:
    ServerDirectives();
    ServerDirectives(std::multimap<std::string, std::vector<std::string> >);
    std::map<int, std::string> &get_error_pages();
    std::string get_default_error_page();
    double    &get_execution_time_limit();
    double    &get_body_max_size();
};

#endif