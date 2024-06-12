/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetClass.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:02:30 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:02:31 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETCLASS_HPP
# define GETCLASS_HPP

#include "../HttpRequestHandler/HttpRequestHandler.hpp"

class GetClass:public HttpRequestHandler
{
private:

public:
    void    handle_static_file();
    void    get_auto_index();
    void     handle_dir_request();
};

//handle_get_method file
void	handle_get_method(int recv_return_value, std::string &header, int client_fd, ParseConfig &config);

#endif