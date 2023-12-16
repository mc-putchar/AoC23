/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 06:05:03 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/16 06:05:03 by mcutura          ###   ########.fr       */
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

	while (std::getline(file, line)) {
		lines.push_back(line);
	}
	file.close();
	std::cout	<< "Result 1: "
				<< energize(lines, Point(0, 0, false, false))
				<< std::endl;
	std::cout	<< "Result 2: "
				<< max_nrg(lines)
				<< std::endl;
	return 0;
}

int	max_nrg(StringVector const &field)
{
	Point	start(0, 0, false, false);
	int		max(0);

	for (size_t y = 0; y < field.size(); ++y) {
		start.y = y;
		start.x = 0;
		start.neg = false;
		max = std::max(max, energize(field, start));
		start.x = field.size() - 1;
		start.neg = true;
		max = std::max(max, energize(field, start));
	}
	start.vert = true;
	for (size_t x = 0; x < field[0].length(); ++x) {
		start.x = x;
		start.y = 0;
		start.neg = false;
		max = std::max(max, energize(field, start));
		start.y = field[0].length() - 1;
		start.neg = true;
		max = std::max(max, energize(field, start));
	}
	return max;
}

int	energize(StringVector const &field, Point pos)
{
	StringVector		result(field);
	std::set<Point>		visited;
	std::queue<Point>	tiles;

	tiles.push(pos);
	while (!tiles.empty()) {
		bool	split(false);
		pos = tiles.front();
		tiles.pop();
		if (pos.x < 0 || static_cast<size_t>(pos.x) >= field[0].length()
		|| pos.y < 0 || static_cast<size_t>(pos.y) >= field.size()) {
			continue;
		}
		switch (field[pos.y][pos.x]) {
			case '-':
				if (visited.find(pos) != visited.end())	continue;
				if (pos.vert) {
					pos.vert = !pos.vert;
					split = true;
				}
				break;
			case '|':
				if (visited.find(pos) != visited.end())	continue;
				if (!pos.vert) {
					pos.vert = !pos.vert;
					split = true;
				}
				break;
			case '/':
				pos.neg = !pos.neg;
				pos.vert = !pos.vert;
				break;
			case '\\':
				pos.vert = !pos.vert;
				break;
			case '.':
			default: break;
		}
		visited.insert(pos);
		if (split) {
			Point	other(pos);
			other.neg = !other.neg;
			other.x += (-2 * other.neg + 1) * !other.vert;
			other.y += (-2 * other.neg + 1) * other.vert;
			tiles.push(other);
		}
		pos.x += (-2 * pos.neg + 1) * !pos.vert;
		pos.y += (-2 * pos.neg + 1) * pos.vert;
		tiles.push(pos);
	}
	// for (std::set<Point>::const_iterator it = visited.begin();
	// it != visited.end(); ++it) {
	// 	result[it->y][it->x] = '#';
	// }
	// std::cout << std::endl;
	// for (StringVector::const_iterator it = result.begin();
	// it != result.end(); ++it) {
	// 	std::cout << *it << std::endl;
	// }
	return visited.size();
}
