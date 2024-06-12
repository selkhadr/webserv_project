/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:29:35 by sbellafr          #+#    #+#             */
/*   Updated: 2024/06/07 20:49:25 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void ft_errors(int select_fd)
{
    if (select_fd < 0)
    {
        std::cerr << "Select error" << std::endl;
        throw std::runtime_error("Select error");
    }
 
}