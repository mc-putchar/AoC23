/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brick.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 06:48:47 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/22 06:48:47 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brick.hpp"

////////////////////////////////////////////////////////////////////////////////
// --- Canonical ---

Brick::Brick(Point3 a, Point3 b) {
	if (a.z < b.z) {
		this->top_ = b;
		this->bottom_ = a;
	} else {
		this->top_ = a;
		this->bottom_ = b;
	}
}

Brick::~Brick() {}

Brick::Brick(Brick const &rhs) {
	std::pair<Point3, Point3>	tmp(rhs.points());
	this->top_ = tmp.first;
	this->bottom_ = tmp.second;
}

Brick &Brick::operator=(Brick const &rhs)
{
	if (this != &rhs) {
		std::pair<Point3, Point3>	tmp(rhs.points());
		this->top_ = tmp.first;
		this->bottom_ = tmp.second;
	}
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
// --- Operator overloads ---

bool Brick::operator<(Brick const &rhs) const
{
	return (this->bottom() < rhs.bottom());
}

std::ostream &operator<<(std::ostream &oss, Brick const &rhs)
{
	std::pair<Point3, Point3> ps(rhs.points());
	oss << ps.second.x << "," << ps.second.y << "," << ps.second.z << "~"
	<< ps.first.x << "," << ps.first.y << "," << ps.first.z;
	return oss;
}

////////////////////////////////////////////////////////////////////////////////
// --- Getters/Setters ---

int Brick::top() const
{
	return this->top_.z;
}

int Brick::bottom() const
{
	return this->bottom_.z;
}

int Brick::front() const
{
	return (this->top_.y > this->bottom_.y ? this->top_.y : this->bottom_.y);
}

int Brick::back() const
{
	return (this->top_.y < this->bottom_.y ? this->top_.y : this->bottom_.y);
}

int Brick::left() const
{
	return (this->top_.x < this->bottom_.x ? this->top_.x : this->bottom_.x);
}

int Brick::right() const
{
	return (this->top_.x > this->bottom_.x ? this->top_.x : this->bottom_.x);
}

std::pair<Point3, Point3> Brick::points() const
{
	return std::make_pair(this->top_, this->bottom_);
}

////////////////////////////////////////////////////////////////////////////////
// --- Methods ---

void Brick::drop(int h)
{
	if (h < 1) { return; }
	this->top_.z -= h;
	this->bottom_.z -= h;
}

bool Brick::intersects(Brick const &rhs) const
{
	if (this->right() < rhs.left() || rhs.right() < this->left()
	|| this->front() < rhs.back() || rhs.front() < this->back()) {
		return false;
	}
	return true;
}
