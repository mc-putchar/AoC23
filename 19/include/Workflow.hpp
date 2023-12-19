/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Workflow.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 06:12:19 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/19 06:12:19 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKFLOW_HPP
# define WORKFLOW_HPP

# include <cstddef>
# include <iostream>
# include <list>
# include <string>
# include <sstream>
# include <vector>

typedef uint16_t							t_rating;
typedef uint64_t							t_comb_rating;
typedef std::pair<uint32_t, std::string>	Match;

union u_rating {
	t_comb_rating	total;
	t_rating		x[4];
	u_rating() : total(0) {}
	u_rating(t_comb_rating n) : total(n) {}
	u_rating(u_rating const &rhs) : total(rhs.total) {}
	u_rating &operator=(u_rating const &rhs) {
		total = rhs.total;
		return *this;
	}
	bool operator<(u_rating const &rhs) {
		return (x[0] < rhs.x[0] && x[1] < rhs.x[1]
			&& x[2] < rhs.x[2] && x[3] < rhs.x[3]);
	}
};

struct Part {
	u_rating	xmas;

	Part(int xcool, int musical, int aero, int shiny) {
		this->xmas.x[0] = (xcool & 0xFFFF);
		this->xmas.x[1] = (musical & 0xFFFF);
		this->xmas.x[2] = (aero & 0xFFFF);
		this->xmas.x[3] = (shiny & 0xFFFF);
	}
	Part(t_comb_rating xmas) {
		this->xmas.total = xmas;
	}
	~Part() {}
	Part(Part const &rhs) {
		this->xmas = rhs.xmas;
	}
	Part &operator=(Part const &rhs) {
		if (&rhs != this) {
			this->xmas = rhs.xmas;
		}
		return *this;
	}
	t_rating	rate() const {
		return (this->xmas.x[0] + this->xmas.x[1]
			+ this->xmas.x[2] + this->xmas.x[3]);
	}
	std::string	to_str() const {
		return ((std::ostringstream()
				<< std::dec << "x=" << this->xmas.x[0]
				<< ",m=" << this->xmas.x[1]
				<< ",a=" << this->xmas.x[2]
				<< ",s=" << this->xmas.x[3]).str());
	}
};

struct Rule {
	t_rating	val;
	short int	offset;
	bool		less;
	std::string	dest;

	Rule(std::pair<char, int> const &cond, bool less, std::string const &dest)
	: val(cond.second & 0xFFFF), offset(0), less(less), dest(dest) {
		switch (cond.first) {
			case 'x':	break;
			case 'm':	this->offset = 1; break;
			case 'a':	this->offset = 2; break;
			case 's':	this->offset = 3; break;
			default:	break;
		}
	}
	~Rule() {}
	Rule(Rule const &rhs) {
		this->offset = rhs.offset;
		this->val = rhs.val;
		this->less = rhs.less;
		this->dest = rhs.dest;
	}
	Rule &operator=(Rule const &rhs) {
		if (&rhs != this) {
			this->offset = rhs.offset;
			this->val = rhs.val;
			this->less = rhs.less;
			this->dest = rhs.dest;
		}
		return *this;
	}
	bool accept(Part const &rhs) const {
		return (this->less ?	rhs.xmas.x[this->offset] < this->val
							:	rhs.xmas.x[this->offset] > this->val);
	}
	uint32_t summary() const {
		unsigned int	lim(this->val);
		if (!less)		{ lim = (lim << 16) | 4001U; }
		return ((lim << 2) | (this->offset & 0x3));
	}
};

class Workflow {
	public:
		Workflow(std::string const &name);
		~Workflow();
		Workflow(Workflow const &rhs);
		Workflow &operator=(Workflow const &rhs);

		std::string const &name() const;
		std::string const &final() const;
		std::list<Rule> const &rules() const;
		void add_rule(Rule const &rule);
		void set_final(std::string const &final);

		std::string			process(Part const &part) const;
		std::vector<Match>	summarize() const;
		std::string			to_str() const;

	private:
		std::string		name_;
		std::string		final_;
		std::list<Rule>	rules_;
};

std::ostream &operator<<(std::ostream &oss, Part const &part);
std::ostream &operator<<(std::ostream &oss, Workflow const &wflow);

#endif // WORKFLOW_HPP
