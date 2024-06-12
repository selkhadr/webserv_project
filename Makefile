SRCS = main.cpp \
       DeleteClass/handle_delete_method.cpp \
       DeleteClass/responce/handle_file_type.cpp \
       DeleteClass/responce/handle_dir_request.cpp \
       GetClass/handle_get_method.cpp \
       GetClass/responce/handle_static_file.cpp \
       GetClass/responce/handle_dir_request.cpp \
       PostClass/handle_post_method.cpp \
       PostClass/request/is_post_req_well_formed.cpp \
       PostClass/request/parce_request.cpp \
       PostClass/responce/handle_static_file.cpp \
       PostClass/responce/handle_dir_request.cpp \
       PostClass/responce/upload_manually.cpp \
       HttpRequestHandler/LocationDirectives/LocationDirectives.cpp \
       HttpRequestHandler/request/check_path_existence.cpp \
       HttpRequestHandler/request/check_request.cpp \
       HttpRequestHandler/request/set_most_significant_location_directives.cpp \
       HttpRequestHandler/request/set_server_directives.cpp \
       HttpRequestHandler/request/find_most_significant_location.cpp \
       HttpRequestHandler/request/get_matched_location_for_request_url.cpp \
       HttpRequestHandler/request/get_requested_resource_path.cpp \
       HttpRequestHandler/request/is_location_has_redirection.cpp \
       HttpRequestHandler/request/is_method_allowed_in_location.cpp \
       HttpRequestHandler/request/handle_dir_request.cpp \
       HttpRequestHandler/request/if_location_has_cgi.cpp \
       HttpRequestHandler/request/extract_request_headers.cpp \
       HttpRequestHandler/request/get_resource_type.cpp \
       HttpRequestHandler/request/prepare_and_execute_cgi.cpp \
       HttpRequestHandler/request/cgi_utils.cpp \
       HttpRequestHandler/HttpRequestHandler.cpp \
       HttpRequestHandler/ServerDirectives/ServerDirectives.cpp \
       HttpRequestHandler/request/is_valid_http_header.cpp \
       HttpRequestHandler/request/is_req_well_formed.cpp \
       HttpRequestHandler/response/send_status_code_response.cpp \
       HttpRequestHandler/response/utils.cpp \
       HttpRequestHandler/response/send_response_file.cpp \
       HttpRequestHandler/response/generate_response_headers.cpp \
       FlowControlException.cpp \
       HttpRequestHandler/request/send_default_error_page.cpp \
       parsing/ParseConfig.cpp \
	parsing/check_directive.cpp \
	parsing/ParseConfig_utils.cpp \
	parsing/parse_server_block.cpp \
	parsing/parse_location_block.cpp \
	parsing/Server.cpp \
       parsing/Location.cpp \
        webserv.cpp Request.cpp \
        ft_errors.cpp \
       parsingBridge.cpp \
        webservutils.cpp \

OBJS = $(SRCS:.cpp=.o)

CPPFLAGS =  -g -std=c++98 -fsanitize=address -Wall -Werror -Wextra

CC = c++

EXECUTION = webserv

all:$(EXECUTION)

%.o:	%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(EXECUTION):	$(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(EXECUTION)

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(EXECUTION)
re: fclean all
