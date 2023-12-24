/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 06:48:09 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/24 06:48:09 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_HPP
# define RAY_HPP

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
	bool operator==(Point3 const &rhs) const {
		return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.y);
	}
};

struct Point3L
{
	size_t	x, y, z;

	Point3L() : x(0), y(0), z(0) {}
	~Point3L() {}
	Point3L(size_t x, size_t y, size_t z) : x(x), y(y), z(z) {}
	Point3L(Point3L const &rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
	Point3L &operator=(Point3L const &rhs) {
		if (this != &rhs) {
		this->x = rhs.x; this->y = rhs.y; this->z = rhs.z;
		}
		return *this;
	}
	Point3L &operator+=(Point3L const &rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		this->y += rhs.y;
		return *this;
	}
	Point3L &operator-=(Point3L const &rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->y -= rhs.y;
		return *this;
	}
	bool operator==(Point3L const &rhs) const {
		return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.y);
	}
};

class Ray
{
	public:
	Ray();
	~Ray();
	Ray(Point3L origin, Point3 velocity);
	Ray(Ray const &rhs);
	Ray &operator=(Ray const &rhs);

	Point3L const &origin() const;
	Point3 const &velocity() const;

	int cross_2d(Ray const &rhs) const;
	bool intersects(Ray const &rhs, long long int min, long long int max) const;
	bool is_ahead(Point3L const &p) const;

	private:
	Point3L	origin_;
	Point3	velocity_;
};

std::ostream &operator<<(std::ostream &oss, Ray const &rhs);

#endif // RAY_HPP
