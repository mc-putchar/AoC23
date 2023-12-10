/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 05:47:13 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/10 10:07:28 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)				return 1;
	std::ifstream				file(av[1]);
	std::string					line;
	std::vector<Point>			chain;

	if (!file.is_open())		return 1;
	std::vector<std::string>	maze;
	while (std::getline(file, line) && !line.empty()) {
		maze.push_back(line);
	}
	file.close();
	std::cout	<< "Result 1: " << get_away(maze, chain) << std::endl;
	std::cout	<< "Result 2: " << find_nesting_area(chain) << std::endl;
	return 0;
}

static Point	find_animal(std::vector<std::string> const &maze)
{
	size_t	y(0);

	while (y < maze.size()) {
		size_t	x(0);
		while (x < maze[y].length()) {
			if (maze[y][x] == 'S')	return Point(y, x);
			++x;
		}
		++y;
	}
	std::cerr << "ERR - no animal found" << std::endl;
	std::exit(1);
}

static std::vector<Point>	orient(std::vector<std::string> const &maze, \
	Point const &start)
{
	std::vector<Point>		points;

	if ((start.x > 1 && maze[start.y][start.x - 1] == '-') \
	|| (start.x && (maze[start.y][start.x - 1] == 'F' \
	|| maze[start.y][start.x - 1] == 'L'))) {
		points.push_back(Point(start.y, start.x - 1));
	}
	if ((static_cast<size_t>(start.y + 2) < (maze.size()) \
	&& maze[start.y + 1][start.x] == '|') \
	|| (static_cast<size_t>(start.y + 1) < (maze.size()) \
	&& (maze[start.y + 1][start.x] == 'L' \
	|| maze[start.y + 1][start.x] == 'J'))) {
		points.push_back(Point(start.y + 1, start.x));
	}
	if ((start.y > 1 && maze[start.y - 1][start.x] == '|') \
	|| (start.y > 0 && (maze[start.y - 1][start.x] == 'F' \
	|| maze[start.y - 1][start.x] == '7'))) {
		points.push_back(Point(start.y - 1, start.x));
	}
	if ((static_cast<size_t>(start.x + 2) < (maze[start.y].length()) \
	&& maze[start.y][start.x + 1] == '-') \
	|| (static_cast<size_t>(start.x + 1) < (maze[start.y].length()) \
	&& (maze[start.y][start.x + 1] == '7' \
	|| maze[start.y][start.x + 1] == 'J'))) {
		points.push_back(Point(start.y, start.x + 1));
	}
	return points;
}

static Point	next_step(std::vector<std::string> const &maze, \
	Point const &cur, Point const &prev)
{
	switch(maze[cur.y][cur.x]) {
		case '|':
			return (cur.y > prev.y ? Point(cur.y + 1, cur.x) : Point(cur.y - 1, cur.x));
		case '-':
			return (cur.x > prev.x ? Point(cur.y, cur.x + 1) : Point(cur.y, cur.x - 1));
		case 'L':
			return (cur.y > prev.y ? Point(cur.y, cur.x + 1) : Point(cur.y - 1, cur.x));
		case 'J':
			return (cur.y > prev.y ? Point(cur.y, cur.x - 1) : Point(cur.y - 1, cur.x));
		case '7':
			return (cur.y < prev.y ? Point(cur.y, cur.x - 1) : Point(cur.y + 1, cur.x));
		case 'F':
			return (cur.y < prev.y ? Point(cur.y, cur.x + 1) : Point(cur.y + 1, cur.x));
		case '.':
			std::cerr	<< "ERR - open pipe end reached"
						<< std::endl;
			std::exit(1);
		case 'S':
			std::cerr	<< "ERR - back at animal or duplicate animal detected"
						<< std::endl;
			std::exit(1);
		default:
			std::cerr	<< "ERR - unrecognized symbol"
						<< std::endl;
			std::exit(1);
	}
}

int	get_away(std::vector<std::string> const &maze, std::vector<Point> &chain)
{
	Point				start(find_animal(maze));
	std::vector<Point>	nexts(orient(maze, start));
	std::vector<Point>	prevs;
	int					steps(1);

	chain.push_back(start);
	chain.insert(chain.begin(), nexts[1]);
	chain.push_back(nexts[0]);
	while (nexts.size() == 2 && nexts[0] != nexts[1]) {
		std::vector<Point>	tmp(nexts);
		if (prevs.empty()) {
			prevs.push_back(start);
			prevs.push_back(start);
		}
		nexts[0] = next_step(maze, nexts[0], prevs[0]);
		nexts[1] = next_step(maze, nexts[1], prevs[1]);
		chain.insert(chain.begin(), nexts[1]);
		chain.push_back(nexts[0]);
		prevs = tmp;
		++steps;
	}
	std::rotate(chain.begin(), \
		std::find(chain.begin(), chain.end(), start), \
		chain.end());
	if (nexts.size() == 2 && nexts[0] == nexts[1])	return steps;
	std::cerr << "ERR - miscalculated steps" << std::endl;
	std::exit(1);
}

// using Pick's theorem for area of simple polygon
int	find_nesting_area(std::vector<Point> const &chain)
{
	int			area(0);

	for (size_t i = 0; i < chain.size() - 1; ++i) {
		area += chain[i].x * chain[i + 1].y - chain[i + 1].x * chain[i].y;
	}
	area += chain.back().x * chain[0].y - chain[0].x * chain.back().y;
	area = std::abs(area) >> 1;
	return (area - (chain.size() >> 1) + 1);
}
