/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 06:04:59 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/16 06:04:59 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <algorithm>
# include <fstream>
# include <iostream>
# include <queue>
# include <set>
# include <string>
# include <vector>

typedef std::vector<std::string> StringVector;

struct Point {
	Point(int x, int y, bool v, bool n) : x(x), y(y), vert(v), neg(n) {}
	Point(Point const &rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		this->vert = rhs.vert;
		this->neg = rhs.neg;
	}
	Point &operator=(Point const &rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		this->vert = rhs.vert;
		this->neg = rhs.neg;
		return *this;
	}
	int	x;
	int	y;
	bool vert;
	bool neg;
};

bool operator<(Point const &lhs, Point const &rhs)
{
	if (lhs.y < rhs.y)	return true;
	if (lhs.y > rhs.y)	return false;
	return (lhs.x < rhs.x);
}

int	energize(StringVector const &field, Point pos);
int	max_nrg(StringVector const &field);

#endif // HEAD_HPP
