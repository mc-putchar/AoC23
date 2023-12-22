/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brick.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 06:43:00 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/22 06:43:00 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRICK_HPP
# define BRICK_HPP

# include <ostream>
# include <utility>

struct Point3
{
	int	x, y, z;

	Point3() : x(0), y(0), z(0) {}
	~Point3() {}
	Point3(int x, int y, int z) : x(x), y(y), z(z) {}
	Point3(Point3 const &rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
	Point3 &operator=(Point3 const &rhs) {
		if (this != &rhs) {
		this->x = rhs.x; this->y = rhs.y; this->z = rhs.z;
		}
		return *this;
	}
	bool operator==(Point3 const &rhs) {
		return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.y);
	}
};

class Brick
{
	public:
	Brick(Point3 a, Point3 b);
	~Brick();
	Brick(Brick const &rhs);
	Brick &operator=(Brick const &rhs);

	bool operator<(Brick const &rhs) const;

	int top() const;
	int bottom() const;
	int front() const;
	int back() const;
	int left() const;
	int right() const;
	std::pair<Point3, Point3> points() const;

	void drop(int h);
	bool intersects(Brick const &rhs) const;

	private:
	Point3	top_, bottom_;

	// deleted
	Brick();
};

std::ostream &operator<<(std::ostream &oss, Brick const &rhs);

#endif // BRICK_HPP
