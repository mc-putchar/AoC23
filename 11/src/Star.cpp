/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Star.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:49:48 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/11 07:49:48 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Star.hpp>


Star::Star(int x, int y) : x_(x), y_(y)
{}

Star::~Star()
{}

Star::Star(Star const &rhs)
{
	this->x_ = rhs.x();
	this->y_ = rhs.y();
}

Star &Star::operator=(Star const &rhs)
{
	if (this != &rhs) {
		this->x_ = rhs.x();
		this->y_ = rhs.y();
	}
	return *this;
}

int Star::x() const
{
	return this->x_;
}

int Star::y() const
{
	return this->y_;
}

int Star::distance(Star const &rhs) const
{
	return (std::abs(rhs.x() - this->x_) + std::abs(rhs.y() - this->y_));
}

