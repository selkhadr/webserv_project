/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:20:38 by sbellafr          #+#    #+#             */
/*   Updated: 2024/06/07 20:49:31 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <pthread.h>
#include <exception>
#include <fcntl.h>
#include <vector>
#include "Request.hpp"


class Request;
class webserv
{
private:
	int port;
	int ser_fd;
	std::string address;
	struct sockaddr_in addr;
	

public:
	webserv(int port, std::string address);
	~webserv();
	int get_port();
	std::string get_address();
	int get_ser_fd();
	void socket_create();
	struct sockaddr_in& addr_get();
	
};

class converter
{
public:
	static void copy_from_file(std::string &bufferprint, std::string &filename);
};
typedef struct Client
{
	std::string buffer;
	std::string bufferprint;
	std::string remaining_data;
	size_t response_sent;
	int client_fd;
	int total;
	int bytes_received;
	int received;
	int count;
	int total_sent;
	std::string response;
	    time_t last_active;
		std::string request;
		


} Clients;
void ft_errors(int select_fd);
#endif