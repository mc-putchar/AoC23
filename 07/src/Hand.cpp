/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hand.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:21:40 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/07 13:21:40 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Hand.hpp"

////////////////////////////////////////////////////////////////////////////////
//  -- PRIVATE HELPERS --

static int	calc_pow(std::set<char> const &uniq, std::string const &raw)
{
	switch (uniq.size()) {
		case 1:	return 6;
		case 2:
			for (std::set<char>::const_iterator it = uniq.begin(); \
			it != uniq.end(); std::advance(it, 1))
				if (std::count(raw.begin(), raw.end(), *it) == 4)
					return 5;
			return 4;
		case 3:
			for (std::set<char>::const_iterator it = uniq.begin(); \
			it != uniq.end(); std::advance(it, 1))
				if (std::count(raw.begin(), raw.end(), *it) == 3)
					return 3;
			return 2;
		case 4:		return 1;
		default:	return 0;
	};
}

static bool	is_second_stronger(std::string const &h1, std::string const &h2)
{
	std::string::size_type	i(0);

	while (i < h1.size()) {
		if (h1[i] == h2[i] && ++i)	continue;
		if (isdigit(h1[i]))
			return (isdigit(h2[i]) ? (h1[i] < h2[i]) : true);
		if (isdigit(h2[i]))
			return false;
		switch (h1[i]) {
			case 'K':	return (h2[i] == 'A');
			case 'Q':	return (h2[i] == 'A' || h2[i] == 'K');
			case 'J':	return (h2[i] != 'J' && h2[i] != 'T');
			case 'T':	return (h2[i] != 'T');
			default:	return false;
		}
	}
	return false;
}

static bool	is_second_stronger_jkr(std::string const &h1, std::string const &h2)
{
	std::string::size_type	i(0);

	while (i < h1.size()) {
		if (h1[i] == h2[i] && ++i)	continue;
		if (h1[i] == 'J')			return true;
		if (h2[i] == 'J')			return false;
		if (isdigit(h1[i]))
			return (isdigit(h2[i]) ? (h1[i] < h2[i]) : true);
		if (isdigit(h2[i]))
			return false;
		switch (h1[i]) {
			case 'K':	return (h2[i] == 'A');
			case 'Q':	return (h2[i] == 'A' || h2[i] == 'K');
			case 'T':	return (h2[i] != 'T');
			default:	return false;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////
//  -- CTORs/DTOR --

Hand::Hand(std::string const &hand, int bet) : \
	raw_(hand), bet_(bet), jokers_(false)
{
	std::string::size_type	i(0);

	while (i < this->raw_.size())
		this->uniq_.insert(this->raw_[i++]);
	this->pow_ = calc_pow(this->uniq_, this->raw_);
}

Hand::Hand(Hand const &cpy)
{
	this->raw_ = cpy.raw_;
	this->bet_ = cpy.bet_;
	this->pow_ = cpy.pow_;
	this->uniq_ = cpy.uniq_;
	this->jokers_ = cpy.jokers_;
}

Hand::~Hand() {}

////////////////////////////////////////////////////////////////////////////////
//  -- OPERATORS --

Hand &Hand::operator=(Hand const &rhs)
{
	if (this != &rhs) {
		this->raw_ = rhs.raw_;
		this->bet_ = rhs.bet_;
		this->pow_ = rhs.pow_;
		this->uniq_ = rhs.uniq_;
		this->jokers_ = rhs.jokers_;
	}
	return *this;
}

bool Hand::operator<(Hand const &rhs)
{
	if (this->pow_ < rhs.pow_)
		return true;
	if (this->pow_ == rhs.pow_)
		return ((this->jokers_) ? is_second_stronger_jkr(this->raw_, rhs.raw_) \
				: is_second_stronger(this->raw_, rhs.raw_));
	return false;
}

////////////////////////////////////////////////////////////////////////////////
//  -- GETTERS --

std::string const	&Hand::raw() const
{
	return this->raw_;
}

int	Hand::bet() const
{
	return this->bet_;
}

int	Hand::pow() const
{
	return this->pow_;
}

////////////////////////////////////////////////////////////////////////////////
//  -- METHODS --

void	Hand::use_jokers()
{
	int	j(std::count(this->raw_.begin(), this->raw_.end(), 'J'));
	int	c(this->uniq_.size());

	this->jokers_ = true;
	switch (j) {
		case 1:
			if (c == 5 || c == 2)	++(this->pow_);
			else					this->pow_ = this->pow_ + 2;
			break;
		case 2:
			if (c == 2 || c == 4)	this->pow_ = this->pow_ + 2;
			else if (c == 3)		this->pow_ = this->pow_ + 3;
			break;
		case 3:
			if (c == 2 || c == 3)	this->pow_ = this->pow_ + 2;
			break;
		case 4:
			if (c == 2)				++(this->pow_);
			break;
		default:
			break;
	}
}
