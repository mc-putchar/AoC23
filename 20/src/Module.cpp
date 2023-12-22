/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Module.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 06:49:44 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/20 06:49:44 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Module.hpp"

////////////////////////////////////////////////////////////////////////////////
// --- Canonical ---

Module::Module() : state_(false) {}

Module::~Module() {}

Module::Module(Module const &rhs) : state_(rhs.test())
{
	for (StringVector::const_iterator it = rhs.dest().begin();
	it != rhs.dest().end(); ++it) {
		this->dest_.push_back(*it);
	}
}

Module &Module::operator=(Module const &rhs)
{
	if (this != &rhs) {
		this->state_ = rhs.test();
		this->dest_.clear();
		for (StringVector::const_iterator it = rhs.dest().begin();
		it != rhs.dest().end(); ++it) {
			this->dest_.push_back(*it);
		}
	}
	return *this;
}

Flipflop::Flipflop() : Module() {}

Flipflop::~Flipflop() {}

Flipflop::Flipflop(Flipflop const &rhs) : Module(rhs) {}

Flipflop &Flipflop::operator=(Flipflop const &rhs) {
	if (this != &rhs) {
		Module::operator=(rhs);
	}
	return *this;
}

Conjunction::Conjunction() : Module() {}

Conjunction::~Conjunction() {}

Conjunction::Conjunction(Conjunction const &rhs) : Module(rhs)
{
	for (std::map<std::string, bool>::const_iterator it = rhs.inputs().begin();
	it != rhs.inputs().end(); ++it) {
		this->inputs_.insert(*it);
	}
}

Conjunction &Conjunction::operator=(Conjunction const &rhs)
{
	if (this != &rhs) {
		Module::operator=(rhs);
		for (std::map<std::string, bool>::const_iterator
		it = rhs.inputs().begin();
		it != rhs.inputs().end(); ++it) {
			this->inputs_.insert(*it);
		}
	}
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
// --- Getter/Setter ---

StringVector const &Module::dest() const
{
	return this->dest_;
}

bool Module::has_dest(std::string const &mod) const
{
	return (std::find(this->dest_.begin(), this->dest_.end(), mod)
	!= this->dest_.end());
}

bool Module::test() const
{
	return this->state_;
}

bool Module::set()
{
	return (this->state_ = true);
}

bool Module::reset()
{
	return (this->state_ = false);
}

void Module::add_output(std::string const &out)
{
	this->dest_.push_back(out);
}

bool Flipflop::flip()
{
	return (this->test() ? (this->reset(), false) : (this->set(), true));
}

std::map<std::string, bool>	const &Conjunction::inputs() const
{
	return this->inputs_;;
}

void Conjunction::register_input(std::string const &input)
{
	this->inputs_.insert(std::make_pair(input, false));
}

////////////////////////////////////////////////////////////////////////////////
// --- Methods ---

PulseVector Module::pulse(Pulse const &p)
{
	PulseVector	pv;
	for (StringVector::const_iterator d = this->dest_.begin();
	d != this->dest_.end(); ++d) {
		pv.push_back(std::make_pair(*d, p.second));
	}
	return pv;
}

PulseVector Flipflop::pulse(Pulse const &p)
{
	if (p.second) { return PulseVector(); }
	return Module::pulse(std::make_pair(p.first, this->flip()));
}

PulseVector Conjunction::pulse(Pulse const &p)
{
	this->inputs_.find(p.first)->second = p.second;
	for (std::map<std::string, bool>::const_iterator in = this->inputs_.begin();
	in != this->inputs_.end(); ++ in) {
		if (!in->second) {
			return Module::pulse(std::make_pair(p.first, this->set()));
		}
	}
	return Module::pulse(std::make_pair(p.first, this->reset()));
}

PulseVector Broadcaster::pulse(Pulse const &p)
{
	return Module::pulse(p);
}
