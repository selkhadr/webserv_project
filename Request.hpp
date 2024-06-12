/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 03:21:00 by sbellafr          #+#    #+#             */
/*   Updated: 2024/06/07 22:51:57 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "webserv.hpp"
#define MAX_SIZE 100000
class webserv;

class Request {
	private :
		std::string requests;
public:
    Request();  // Constructor
    ~Request(); // Destructor
	int RequestName(std::string request);
	int server_choice(std::vector<webserv> server, int size, int i);
	int	calculate_content_length(std::string buffer);
	int	find_header_end(const std::string &buffer);
    // Declare other member functions and variables here
};

#endif