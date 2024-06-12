/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostClass.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:24:01 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:24:02 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSTCLASS_HPP
# define POSTCLASS_HPP

# include "../HttpRequestHandler/HttpRequestHandler.hpp"

class PostClass:public HttpRequestHandler
{
private:
    size_t                              content_length;
    std::string                         boundary;
    std::string                         file_content;
    std::string                         file_name;
    struct stat                        stat_of_upload;
public:
    void    parce_request();
    void    is_req_well_formed();
    void    check_content_length();
    void    handle_dir_request();
    void    handle_file_type();
    void    handle_static_file();
    void    execute_post_processing();
    void    upload_manually();
    void    extract_boundary();
    void    extract_file_content();
    void    extract_file_name();
    void    create_and_populate_file();
    void    chuncked_request_to_unchuncked();
};

void handle_post_method(int recv_return_value, std::string header, int client_fd, ParseConfig &config);

#endif