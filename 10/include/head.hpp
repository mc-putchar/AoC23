/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 05:47:03 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/10 05:47:03 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <algorithm>
# include <cstdlib>
# include <fstream>
# include <iostream>
# include <string>
# include <vector>

struct Point
{
	int	y;
	int	x;
	Point(int a, int b) : y(a), x(b) {};
	bool operator==(Point const &rhs) const
		{ return (this->y == rhs.y && this->x == rhs.x); };
	bool operator!=(Point const &rhs) const
		{ return (this->y != rhs.y || this->x != rhs.x); };
};

int	get_away(std::vector<std::string> const &maze, std::vector<Point> &chain);
int	find_nesting_area(std::vector<Point> const &chain);

#endif // HEAD_HPP
