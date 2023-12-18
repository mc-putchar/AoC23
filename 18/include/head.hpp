/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 06:16:59 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/18 06:16:59 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <algorithm>
# include <fstream>
# include <iostream>
# include <sstream>
# include <string>
# include <vector>

typedef std::vector<std::string> StringVector;

struct Point
{
	Point(int a, int b) : y(a), x(b) {};
	Point(Point const &rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
	}
	Point &operator=(Point const &rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}
	bool operator==(Point const &rhs) const
		{ return (this->y == rhs.y && this->x == rhs.x); };
	bool operator!=(Point const &rhs) const
		{ return (this->y != rhs.y || this->x != rhs.x); };
	int	y;
	int	x;
};

struct Edge {
	Edge(int direction, int steps, int color) :
	 dir(direction), step(steps), color(color) {}
	Edge(Edge const &rhs) {
		this->dir = rhs.dir;
		this->step = rhs.step;
		this->color = rhs.color;
	}
	Edge &operator=(Edge const &rhs) {
		this->dir = rhs.dir;
		this->step = rhs.step;
		this->color = rhs.color;
		return *this;
	}
	int	dir;
	int	step;
	int	color;
};

std::vector<Edge>	parse_input(StringVector const &lines, bool swap);
long int			get_area(std::vector<Edge> const &edges);

#endif // HEAD_HPP
