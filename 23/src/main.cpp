/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 06:02:44 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/23 06:02:44 by mcutura          ###   ########.fr       */
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

	std::cout	<< "Result 1: "
				<< longest_path(lines)
				<< std::endl;
	std::cout	<< "Result 2: "
				// << most_scenic_path(lines)
				<< std::endl;
	return 0;
}
