/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 05:57:48 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/17 05:57:48 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <fstream>
# include <iostream>
# include <limits>
# include <queue>
# include <string>
# include <vector>

#define INF	std::numeric_limits<int>::max()

typedef std::vector<std::string> StringVector;

struct Point {
	Point(int x, int y) : x(x), y(y) {}
	Point(Point const &rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
	}
	Point &operator=(Point const &rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}
	int	x;
	int	y;
};

bool operator<(Point const &lhs, Point const &rhs)
{
	if (lhs.y < rhs.y)	return true;
	if (lhs.y > rhs.y)	return false;
	return (lhs.x < rhs.x);
}

typedef std::pair<int, std::pair<Point, int> > Node;

int	find_hottest_path(StringVector const &map, int min_step, int max_step);

#endif // HEAD_HPP
