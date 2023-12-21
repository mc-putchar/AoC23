/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 06:10:00 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/21 06:10:00 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"

namespace {
	static const int	k_steps = 64;
	static const int	k_steps_actual = 26501365;
}

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
				<< count_reachable(lines, k_steps)
				<< std::endl;
	std::cout	<< "Result 2: "
				<< count_parallel(lines, k_steps_actual)
				<< std::endl;
	return 0;
}
