/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Workflow.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 06:13:11 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/19 06:13:11 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Workflow.hpp"

////////////////////////////////////////////////////////////////////////////////
/// --- Canonical ---

Workflow::Workflow(std::string const &name) : name_(name), final_("") {}

Workflow::~Workflow() {}

Workflow::Workflow(Workflow const &rhs)
{
	this->name_ = rhs.name();
	this->final_ = rhs.final();
	for (std::list<Rule>::const_iterator rule = rhs.rules_.begin();
	rule != rhs.rules_.end(); ++rule) {
		this->rules_.push_back(*rule);
	}
}

Workflow &Workflow::operator=(Workflow const &rhs)
{
	if (&rhs != this) {
		this->name_ = rhs.name();
		this->final_ = rhs.final();
		if (!this->rules_.empty()) {
			this->rules_.clear();
		}
		for (std::list<Rule>::const_iterator rule = rhs.rules_.begin();
		rule != rhs.rules_.end(); ++rule) {
			this->rules_.push_back(*rule);
		}
	}
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
/// --- Getter/Setter ---

std::string const &Workflow::name() const
{
	return this->name_;
}

std::string const &Workflow::final() const
{
	return this->final_;
}

std::list<Rule> const &Workflow::rules() const
{
	return this->rules_;
}

void Workflow::add_rule(Rule const &rule)
{
	this->rules_.push_back(rule);
}

void Workflow::set_final(std::string const &final)
{
	this->final_ = final;
}

////////////////////////////////////////////////////////////////////////////////
/// --- Methods ---

std::string Workflow::process(Part const &part) const
{
	for (std::list<Rule>::const_iterator rule = this->rules_.begin();
	rule != rules_.end(); ++rule) {
		if (rule->accept(part)) {
			return rule->dest;
		}
	}
	return this->final_;
}

std::vector<Match> Workflow::summarize() const
{
	std::vector<Match>	matches;

	matches.reserve(this->rules_.size());
	for (std::list<Rule>::const_iterator rule = this->rules_.begin();
	rule != this->rules_.end(); ++rule) {
		matches.push_back(std::make_pair(rule->summary(), rule->dest));
	}
	matches.push_back(std::make_pair(0, this->final_));
	return matches;
}

std::string Workflow::to_str() const
{
	std::string	str(this->name_);
	str.append("{");
	for (std::list<Rule>::const_iterator rule = this->rules_.begin();
	rule != this->rules_.end(); ++rule) {
		str.append(":" + rule->dest + ",");
	}
	str.append(this->final_ + "}");
	return str;
}

////////////////////////////////////////////////////////////////////////////////
/// --- Operators ---

std::ostream &operator<<(std::ostream &oss, Part const &part)
{
	oss	<< part.to_str();
	return oss;
}

std::ostream &operator<<(std::ostream &oss, Workflow const &wflow)
{
	oss	<< wflow.to_str();
	return oss;
}
