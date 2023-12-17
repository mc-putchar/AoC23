/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 05:57:44 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/17 05:57:44 by mcutura          ###   ########.fr       */
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
				<< find_hottest_path(lines, 1, 3)
				<< std::endl;
	std::cout	<< "Result 2: "
				<< find_hottest_path(lines, 4, 10)
				<< std::endl;
	return 0;
}

static int	shortest_dist(std::vector<int> const &dist)
{
	return std::min(std::min(dist[0], dist[1]), std::min(dist[2], dist[3]));
}

int	update_forward_jump(StringVector const &map, Point const &p, int dir,
int min_step, int max_step, int d_so_far, std::vector<std::vector<int> > &dist)
{
	int	x(p.x);
	int	y(p.y);
	int	i(0);
	int	u(0);
	while (i < max_step) {
		x += ((dir + 1) & 1) * (1 - (dir & 2));
		y += (dir & 1) * (1 - (dir & 2));
		if (x < 0 || static_cast<size_t>(x) >= map[0].length()
		|| y < 0 || static_cast<size_t>(y) >= map.size())
			return u;
		d_so_far += map[y][x] - '0';
		if (i < min_step - 1) {
			++i;
			continue;
		}
		if (d_so_far < dist[y * map[0].length() + x][dir]) {
			dist[y * map[0].length() + x][dir] = d_so_far;
			u |= (1 << i);
		}
		++i;
	}
	return u;
}

/* 
 * Compact direction: X+((dir+1)&1)*(1-(dir&2)) , Y+(dir&1)*(1-(dir&2))
 * I <3 bits!
 */
int		find_hottest_path(StringVector const &map, int min_step, int max_step)
{
	int								dir(0);
	size_t							len(map[0].length());
	std::vector<int>				initvec(4, INF);
	std::vector<std::vector<int> >	dist(map.size() * len, initvec);
	std::priority_queue<Node, std::vector<Node>, std::greater<Node> >
		unvisited;

	unvisited.push(std::make_pair(0, std::make_pair(Point(0, 0), 3)));
	for (std::vector<int>::iterator it = dist[0].begin(); 
	it != dist[0].end(); ++it) {
		*it = 0;
	}
	while (!unvisited.empty()) {
		Node	current(unvisited.top());
		Point	p(current.second.first);
		unvisited.pop();
		for (dir = 0; dir < 4; ++dir) {
			if (dir == current.second.second
			|| dir == ((current.second.second + 2) & 3)) {
				if (p.x || p.y)	{ continue; }
			}
			int jmp(update_forward_jump(map, p, dir, min_step, max_step,
				dist[p.y * len + p.x][current.second.second], dist));
			Point	forw(p.x, p.y);
			for (int i = 0; i < max_step; ++i) {
				forw.x += ((dir+1)&1)*(1-(dir&2));
				forw.y += (dir&1)*(1-(dir&2));
				if ((jmp >> i) & 1) {
					unvisited.push(std::make_pair(dist[forw.y*len+forw.x][dir],
								std::make_pair(forw, dir)));
				}
			}
		}
	}
	return shortest_dist(dist.back());
}
