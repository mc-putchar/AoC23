/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 06:40:39 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/22 06:40:39 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Brick.hpp"

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

	std::vector<Brick>	slabs(parse_input(lines));
	settle_down(slabs);
	std::cout	<< "Result 1: "
				<< disintegration_targets(slabs)
				<< std::endl;
	std::cout	<< "Result 2: "
				<< chain_reaction(slabs)
				<< std::endl;
	return 0;
}

std::vector<Brick>	parse_input(StringVector const &input)
{
	std::vector<Brick>	slabs;

	for (StringVector::const_iterator line = input.begin();
	line != input.end(); ++line) {
		int					x, y, z;
		std::stringstream	iss(*line);

		if (line->find('~') == std::string::npos) { continue; }
		iss >> x; iss.ignore(); iss >> y; iss.ignore(); iss >> z; iss.ignore();
		Point3	first(x, y, z);
		iss >> x; iss.ignore(); iss >> y; iss.ignore(); iss >> z;
		slabs.push_back(Brick(first, Point3(x, y, z)));
	}
	return slabs;
}
