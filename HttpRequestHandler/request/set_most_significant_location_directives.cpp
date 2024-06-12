/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_most_significant_location_directives.cp        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:07:56 by selkhadr          #+#    #+#             */
/*   Updated: 2024/06/12 11:07:57 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LocationDirectives/LocationDirectives.hpp"
#include "../HttpRequestHandler.hpp"

void HttpRequestHandler::set_most_significant_location_directives()
{
        LocationDirectives LocationDirectives(locations_as_string[most_significant_location_as_string], server_from_config, client_fd);
        this->most_significant_location_directives = LocationDirectives;
}
