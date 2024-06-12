/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:20:38 by sbellafr          #+#    #+#             */
/*   Updated: 2024/06/12 12:15:57 by sbellafr         ###   ########.fr       */
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
#include "parsing/ParseConfig.hpp"
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
	webserv();
	~webserv();
	int get_port();
	std::string get_address();
	int get_ser_fd();
	void socket_create();
	struct sockaddr_in& addr_get();
	void	processClient(std::vector<Clients> &clients, fd_set &write_fd_set, int i, ParseConfig &Config);
	void	handleClientRequest(Request &request, std::vector<webserv> &server, std::vector<Clients> &clients, int &max, fd_set &read_fd_set, fd_set &write_fd_set, int i, bool &chunked_finished);
	

	
};


int send_http_request(int client_fd, ParseConfig &config, std::string http_request, int recv_value);
void ft_errors(int select_fd);
bool check_chunked(std::string buffer);
int send_http_request(int client_fd, ParseConfig &config, std::string http_request, int recv_value);
void perfect_server();
#endif