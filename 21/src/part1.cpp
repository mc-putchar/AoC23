/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 06:11:24 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/21 06:11:24 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"

static void	flip(StringVector &map, size_t r, size_t c)
{
	if (r && map[r - 1][c] == '.') {
		map[r - 1][c] = 'O';
	}
	if (c && map[r][c - 1] == '.') {
		map[r][c - 1] = 'O';
	}
	if (c + 1 < map[r].length() && map[r][c + 1] == '.') {
		map[r][c + 1] = 'O';
	}
	if (r + 1 < map.size() && map[r + 1][c] == '.') {
		map[r + 1][c] = 'O';
	}
}

StringVector	simulate(StringVector const &map)
{
	StringVector			next(map);
	std::string::size_type	pos;

	for (size_t r = 0; r < map.size(); ++r) {
		pos = 0;
		while ((pos = map[r].find('O', pos)) != std::string::npos) {
			flip(next, r, pos);
			next[r][pos] = '.';
			++pos;
		}
	}
	return next;
}

unsigned int	count_reachable(StringVector lines, int steps)
{
	unsigned int	reachable(0);
	size_t			r(0), c(0);

	for ( ; r < lines.size(); ++r) {
		for (c = 0; c < lines[r].length(); ++c) {
			if (lines[r][c] == 'S') {
				lines[r][c] = 'O';
				break;
			}
		}
		if (c < lines[r].length()) {
			break;
		}
	}
	while (steps--) {
		lines = simulate(lines);
	}
	for (StringVector::const_iterator line = lines.begin();
	line != lines.end(); ++line) {
		reachable += std::count(line->begin(), line->end(), 'O');
	}
	return reachable;
}
