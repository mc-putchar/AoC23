/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 06:52:43 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/24 06:52:43 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ray.hpp"

////////////////////////////////////////////////////////////////////////////////
// --- Canonical ---

Ray::Ray() : origin_(), velocity_() {}

Ray::~Ray() {}

Ray::Ray(Point3L origin, Point3 velocity)
: origin_(origin), velocity_(velocity) {}

Ray::Ray(Ray const &rhs) : origin_(rhs.origin()), velocity_(rhs.velocity()) {}

Ray &Ray::operator=(Ray const &rhs)
{
	if (this != &rhs) {
		this->origin_ = rhs.origin();
		this->velocity_ = rhs.velocity();
	}
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
// --- Operator overloads ---

std::ostream &operator<<(std::ostream &oss, Ray const &rhs)
{
	oss << rhs.origin().x << ", " << rhs.origin().y << ", " << rhs.origin().z
	<< " @ "
	<< rhs.velocity().x << ", " << rhs.velocity().y << ", " << rhs.velocity().z;
	return oss;
}

////////////////////////////////////////////////////////////////////////////////
// --- Getters/Setters ---

Point3L const &Ray::origin() const
{
	return this->origin_;
}

Point3 const &Ray::velocity() const
{
	return this->velocity_;
}

////////////////////////////////////////////////////////////////////////////////
// --- Methods ---

int Ray::cross_2d(Ray const &rhs) const
{
	return (this->velocity_.x * rhs.velocity().y
	- this->velocity_.y * rhs.velocity().x);
}

bool Ray::is_ahead(Point3L const &p) const
{
	if (this->velocity_.x < 0 && this->origin_.x < p.x) return false;
	if (this->velocity_.x > 0 && this->origin_.x > p.x) return false;
	if (this->velocity_.y < 0 && this->origin_.y < p.y) return false;
	if (this->velocity_.y > 0 && this->origin_.y > p.y) return false;
	return true;
}

bool Ray::intersects(Ray const &rhs, long long int min, long long int max) const
{
	int	cross(this->cross_2d(rhs));
	if (!cross) { return false; }

	long long int	xoff(this->origin_.x - rhs.origin().x);
	long long int	yoff(this->origin_.y - rhs.origin().y);
	long long int	tmp(this->velocity_.x * yoff - this->velocity_.y * xoff);
	double			t(static_cast<double>(tmp) / cross);
	long long int	interx(static_cast<long long int>
					(t * rhs.velocity().x + rhs.origin().x));
	long long int	intery(static_cast<long long int>
					(t * rhs.velocity().y + rhs.origin().y));

	if (interx < min || interx > max || intery < min || intery > max) {
		return false;
	}
	Point3L		p(static_cast<size_t>(interx), static_cast<size_t>(intery), 0);
	if (!this->is_ahead(p) || !rhs.is_ahead(p)) {
		return false;
	}
	return true;
}
