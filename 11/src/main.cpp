/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:14:14 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/11 09:52:22 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Star.hpp"

namespace {
	static int const	k_multi = 1000000;
}

int	main(int ac, char **av)
{
	if (ac != 2)				return 1;
	std::ifstream				file(av[1]);
	std::string					line;
	std::vector<std::string>	universe;
	std::vector<size_t>			empty_rows;
	std::vector<size_t>			empty_cols;

	if (!file.is_open())		return 1;
	while (std::getline(file, line) && !line.empty()) {
		universe.push_back(line);
	}
	file.close();
	expand(universe, empty_rows, empty_cols);
	std::cout	<< "Result 1: "
				<< measure(universe, empty_rows, empty_cols, 1)
				<< std::endl;
	std::cout	<< "Result 2: "
				<< measure(universe, empty_rows, empty_cols, k_multi - 1)
				<< std::endl;
	return 0;
}

void	expand(std::vector<std::string> &universe,
		std::vector<size_t> &empty_rows,
		std::vector<size_t> &empty_cols)
{
	for (size_t y = 0; y < universe.size(); ++y) {
		if (universe[y].find('#') == std::string::npos) {
			empty_rows.push_back(y);
		}
	}
	for (size_t x = 0; x < universe[0].length(); ++x) {
		bool		empty(true);
		for (size_t y = 0; y < universe.size(); ++y) {
			if (universe[y][x] == '#') {
				empty = false;
				break;
			}
		}
		if (empty)	empty_cols.push_back(x);
	}
}

static int	comp(Star const &alpha_centauri, Star const &sirius_a,
	std::vector<size_t> const &r, std::vector<size_t> const &c)
{
	int	count(0);

	int x1 = std::min(alpha_centauri.x(), sirius_a.x());
	int x2 = std::max(alpha_centauri.x(), sirius_a.x());
	for (int x = x1; x < x2; ++x) {
		if (std::find(c.begin(), c.end(), x) != c.end()) {
			++count;
			// std::cout << "compensating for column " << x << std::endl;
		}
	}
	int y1 = std::min(alpha_centauri.y(), sirius_a.y());
	int y2 = std::max(alpha_centauri.y(), sirius_a.y());
	for (int y = y1; y < y2; ++y) {
		if (std::find(r.begin(), r.end(), y) != r.end()) {
			++count;
			// std::cout << "compensating for row " << y << std::endl;
		}
	}
	return count;
}

uint64_t	measure(std::vector<std::string> const &universe,
			std::vector<size_t> const &empty_rows,
			std::vector<size_t> const &empty_cols,
			int k)
{
	std::map<int, Star>	map;
	int					n(0);
	uint64_t			sum(0);

	for (size_t y = 0; y < universe.size(); ++y) {
		for (size_t x = 0; x < universe[y].length(); ++x) {
			if (universe[y][x] == '#') {
				map.insert(std::make_pair(++n, Star(x, y)));
			}
		}
	}
	for (std::map<int, Star>::const_iterator it = map.begin(); \
	it != (map.end()); ++it) {
		for (std::map<int, Star>::const_iterator rhs = it; \
		rhs != map.end();) {
			if (++rhs == map.end())		break;
			int d = it->second.distance(rhs->second);
			uint64_t c = comp(it->second, rhs->second, empty_rows, empty_cols);
			sum += c * k + d;
		}
	}
	return sum;
}
