/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 05:57:58 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/08 09:20:38 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Utils.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)	return 1;

	std::ifstream	file(av[1]);
	std::string		instructions;
	std::string		line;
	NavMap			map;

	if (!file.is_open())	return 1;

	if (!std::getline(file, instructions) || instructions.empty())	return 1;

	while (std::getline(file, line)) {
		if (line.empty())				continue;
		std::string::size_type			pos(line.find(" = "));
		if (pos == std::string::npos)	continue;
		std::string						key(line.substr(0, pos));
		std::vector<std::string>		tmp(ft_splitstr(&line[pos + 3], " ,()"));

		if (tmp.size() != 2)			return (file.close(), 1);
		map.insert(std::make_pair(key, std::make_pair(tmp[0], tmp[1])));
	}
	file.close();

	if (map.find("AAA") != map.end() && map.find("ZZZ") != map.end())
		std::cout	<< "Result 1: " \
					<< follow_steps(instructions, map) << std::endl;
	std::cout	<< "Result 2: " \
				<< ghost_steps(instructions, map) << std::endl;
	return 0;
}

int	follow_steps(std::string const &instr, NavMap const &map)
{
	int		steps(0);
	size_t	i(0);
	MapCIt	pos(map.begin());

	while (pos->first.compare("ZZZ")) {
		if (i == instr.size())	i = 0;
		pos = map.find((instr[i++] == 'L') ? \
			pos->second.first : pos->second.second);
		if (pos == map.end())	return -1;
		++steps;
	}
	return steps;
}

/* LOL brute force takes 4ever, lowest common multiple it is */
uint64_t	ghost_steps(std::string const &instr, NavMap const &map)
{
	std::list<MapCIt>	nodes;
	std::vector<int>	periods;

	for (MapCIt it = map.begin(); it != map.end(); ++it)
		if (*(it->first.rbegin()) == 'A')
			nodes.push_back(it);
	for (std::list<MapCIt>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
		int		steps(0);

		while (*((*it)->first.rbegin()) != 'Z')
			(*it) = map.find((instr[steps++ % instr.size()] == 'L') ? \
					(*it)->second.first : (*it)->second.second);
		periods.push_back(steps);
	}
	std::sort(periods.begin(), periods.end());
	return std::accumulate(periods.begin(), periods.end(), \
		static_cast<uint64_t>(1U), find_lcm);
}

static uint64_t	find_gcd(uint64_t a, uint64_t b)
{
	if (!b || b == a)	return a;
	if (!a)				return b;
	if (a > b) {
		if (!(a % b))	return b;
		return find_gcd(a - b, b);
	}
	if (!(b % a))		return a;
	return find_gcd(a, b - a);
}

uint64_t	find_lcm(uint64_t a, uint64_t b)
{
	uint64_t	gcd(find_gcd(a, b));
	return (gcd ? ((a / gcd) * b) : 0);
}
