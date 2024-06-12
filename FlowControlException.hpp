/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlowControlException.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:24:31 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:24:32 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOWCONTROLEXCEPTION_HPP
#define FLOWCONTROLEXCEPTION_HPP

# include <exception>

class FlowControlException : public std::exception
{
public:
    FlowControlException();
    FlowControlException(int flag);
    int get_flag() const ;
private:
    int flag;
};

#endif