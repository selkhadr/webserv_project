/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequestHandler.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:59:38 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:21:49 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HttpRequestHandler_HPP
# define HttpRequestHandler_HPP

//to delete
# include <stdio.h>

# include <map>
# include <signal.h> 
# include <sys/stat.h>
# include <stdbool.h>
# include <vector>
# include <sstream>
# include <iostream>
# include <arpa/inet.h>
# include <unistd.h>
# include "LocationDirectives/LocationDirectives.hpp"
# include "ServerDirectives/ServerDirectives.hpp"
# include <fstream>
# include <sys/types.h>
# include <dirent.h>
# include <cctype>
# include <fcntl.h>
# include "../FlowControlException.hpp"
# include "../parsing/ParseConfig.hpp"

#define BUFFER_SIZE 1100000

enum Permission {
    READ = R_OK,
    WRITE = W_OK,
    EXECUTE = X_OK
};

class   HttpRequestHandler
{
protected:
	std::map<std::string, std::map<std::string, std::vector<std::string> > >	locations_as_string;
	std::multimap<std::string, std::vector<std::string> >						server_from_config;
	std::map<std::string, std::string>											request_headers;
	std::map<std::string, std::string>											file_types;
	std::vector<std::vector<std::string> >										locations_as_vectors;
	std::vector<std::string>													envp_as_vec;
	std::vector<std::string>													request_url_as_vector;
	LocationDirectives									 						most_significant_location_directives;
	ServerDirectives															server_directives;
	std::string																	most_significant_location_as_string;
	std::string																	request_server_name;
	std::string																	port;
	std::string																	request_method;
	std::string																	request_header;
	std::string																	request_url_as_string;
	std::string																	requested_resource_from_url;
	std::string																	requested_resource_path;
	std::string																	request_body;
	std::string																	response_header;
	std::string																	response_status_line;
	std::string																	response_reason_phrase;
	std::string																	response_headers;
	std::string																	response_content_type;
	std::string																	response_selected_error_page;
	std::string																	response_selected_error_page_path;
	std::string																	response_autoindex;
	std::string																	directory_content_list;
	std::string																	response_body;
	std::string																	http_response;
	std::string																	http_version;
	std::string																	cgi_output;
	std::string																	cgi_output_headers;
	std::string																	requested_file_extension;
	std::string																	cgi_output_body;
	double																		execution_time;
	int																			response_content_length;
	int																			response_status_code;
	int																			client_fd;
	int																			recv_return_value;
	int																			pid;
	int																			cgi_output_pipe[2];
	int																			waitpid_status;
	int																			waitpid_result;
	char																		**envp;
	char																		**argc;
	clock_t																		start_time;
	clock_t																		end_time;
	struct stat																	stat_of_request_resource;
	struct stat																	stat_of_error_page;
	struct dirent *																read_dir;
	DIR *																		dir;
public:

	void			is_valid_request_header(int recv_value, std::string &header, int client_fd, ParseConfig &config);
	void			extract_request_url_as_string_from_header();
	bool			allowed_speciel_character(char c);
	void			url_contain_allowed_characters();
	void			get_matched_location_for_request_url();
	void			build_request_url_as_vectors();
	void			build_locations_as_vector();
	void		 	find_semilare_locations_to_url(std::vector<std::string> &request_url_as_vector, std::vector<std::vector<std::string> > &locations_as_vectors);
	std::string 	vector_to_string(std::vector<std::string>&locations_as_vectors);
	std::string 	find_most_significant_location(std::vector<std::string> &request_url_as_vector, std::vector<std::vector<std::string> > local_locations_as_vectors);
	void			set_most_significant_location_directives();
	void			is_location_has_redirection();
	bool 			check_path_existence();
	void			is_method_allowed_in_location();
	void			set_request_method(std::string request_method);
	void			get_requested_resource_path();
	void			extract_requested_resource_from_url();
	void			build_requested_resource_path();
	void			set_server_directives();
	void 			send_status_code_response(int code_status, std::string reason_phrase);
	int 			generate_response_status_line(int response_status_code, std::string response_reason_phrase);
	int 			generate_status_code_headers(int is_redirection_response);
	void 			generate_file_content_as_response_body(std::string requested_resource_path);
	void 			send_response();
	int 			generate_body_from_default_error_page();
	void	 		get_resource_type();
	virtual void	is_req_well_formed();
	virtual void	handle_dir_request() = 0;
	virtual void	handle_static_file() = 0;
	virtual void	handle_file_type();
	bool			is_dir_has_index_file();
	int	  			prepare_and_execute_cgi();
	void			extract_request_headers();
	void			env_variables_from_req_headers();
	void			format_keys();
	void			fill_argc();
	int				execute_cgi_script();
	int				generate_data_for_post();
	void			add_standard_CGI_environment_variable();
	void			read_cgi_output_pipe();
	void			generate_response_headers();
	void			initialize_supported_file_types();
	void			determine_content_type();
	void			send_cgi_output_response();
	void			generate_cgi_output_response();
	void			generate_cgi_headers();
	void			parse_cgi_output();
	bool			if_location_has_cgi();
	void			find_port();
	void			check_permission(Permission permission);
	void			find_most_significant_server(ParseConfig &config);
};

int			file_content_to_string(std::string file_name, std::string &response_body);
std::string	integer_to_string(int num);
void		convert_to_uppercase(std::string &key);
char		**copy_vector_to_cstring_array(std::vector<std::string> &vect, int client_fd);
std::string	extract_content_type(const std::string& cgi_output);
void		send_default_error_page(int response_status_code, std::string response_reason_phrase, int client_fd);
#endif