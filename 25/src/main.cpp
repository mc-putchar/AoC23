/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 06:00:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/25 06:00:49 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)				return 1;
	std::ifstream				file(av[1]);
	if (!file.is_open())		return 1;
	std::string					line;
	StringVector				lines;

	while (std::getline(file, line) && !line.empty()) {
		lines.push_back(line);
	}
	file.close();
	// parse_input(lines);
	std::cout	<< "Result 1: "
				// << 
				<< std::endl;
	std::cout	<< "Result 2: "
				// << 
				<< std::endl;
	return 0;
}
