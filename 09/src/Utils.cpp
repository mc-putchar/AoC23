/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 07:26:46 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/04 07:26:46 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

std::vector<std::string> ft_splitstr(std::string string, std::string delims)
{
	std::vector<std::string>	split;
	std::string::size_type		start(0);
	std::string::size_type		end(0);

	while ((end = string.find_first_of(delims, start)) != std::string::npos) {
		if (end > start) {
			split.push_back(string.substr(start, end - start));
			start = end;
		}
		if (++start == string.size())
			break;
	}
	if (end == std::string::npos && start < string.size())
		split.push_back(string.substr(start, string.size()));
	return split;
}
