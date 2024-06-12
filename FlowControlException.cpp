/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlowControlException.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:24:28 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:24:29 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FlowControlException.hpp"

FlowControlException::FlowControlException()
{
    flag = 0;
}

FlowControlException::FlowControlException(int flag):flag(flag)
{

}

int FlowControlException::get_flag() const
{
    return flag;
}
