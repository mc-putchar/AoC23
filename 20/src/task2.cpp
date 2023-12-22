/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:56:06 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/20 10:56:06 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Module.hpp"

static StringVector	select_nands(StringVector const &data)
{
	StringVector	nands;

	for (StringVector::const_iterator it = data.begin();
	it != data.end(); ++it) {
		if ((*it)[0] == '&') {
			std::string::size_type	pos(it->find(' '));
			nands.push_back(it->substr(1, --pos));
		}
	}
	return nands;
}

static StringVector	sort_nands(ModMap const &mods, StringVector const &nands)
{
	StringVector	sorted;

	sorted.reserve(nands.size());
	for (StringVector::const_iterator it = nands.begin();
	it != nands.end(); ++it) {
		if (mods.find(*it)->second->has_dest("rx")) {
			sorted.push_back(*it);
		}
	}
	for (StringVector::const_iterator it = sorted.begin();
	it != sorted.end(); std::advance(it, 1)) {
		Conjunction					*nand(reinterpret_cast<Conjunction*>(
									mods.find(*it)->second));
		std::map<std::string, bool>	ins(nand->inputs());
		for (std::map<std::string, bool>::const_iterator in = ins.begin();
		in != ins.end(); ++in) {
			if (std::find(nands.begin(), nands.end(), in->first)
			!= nands.end()) {
				sorted.push_back(in->first);
			}
		}
	}
	std::reverse(sorted.begin(), sorted.end());
	return sorted;
}

void	print_nands(ModMap const &mods, StringVector const &nands)
{
	for (StringVector::const_iterator it = nands.begin();
	it != nands.end(); ++it) {
			Module						*nand(mods.find(*it)->second);
			std::map<std::string, bool>	ins(reinterpret_cast<Conjunction*>
										(nand)->inputs());
			for (std::map<std::string, bool>::const_iterator in = ins.begin();
			in != ins.end(); ++in) {
				std::cout << in->first << "&";
			}
			std::cout << "> " << *it << " !> ";
			for (StringVector::const_iterator out = nand->dest().begin();
			out != nand->dest().end(); ++out) {
				std::cout << *out << "|";
			}
			std::cout << std::endl;
	}
}

void	print_chains(std::vector<StringVector> const &chains)
{
	for (std::vector<StringVector>::const_iterator it = chains.begin();
	it != chains.end(); ++it) {
		std::cout << "button -> broadcaster -> ";
		for (StringVector::const_iterator node = it->begin() + 1;
		node != it->end(); ++node) {
			std::cout << *node << " -> ";
		}
		std::cout << "!& " << it->front() << " !& CTRLs !& rx" << std::endl;
	}
}

static std::vector<StringVector>	link_latches(ModMap const &mods,
												StringVector const &nands)
{
	ModMap::const_iterator		next(mods.find("broadcaster"));
	StringVector				nodes(next->second->dest());
	std::vector<StringVector>	chains;

	for (StringVector::const_iterator it = nodes.begin();
	it != nodes.end(); ++it) {
		StringVector	chain;
		StringVector	links;
		std::string		node(*it);
		chain.push_back("");
		chain.push_back(node);
		while ((next = mods.find(node)) != mods.end()) {
			links = next->second->dest();
			node = "";
			for (StringVector::const_iterator link = links.begin();
			link != links.end(); ++link) {
				StringVector::const_iterator	nand(std::find(nands.begin(),
												nands.end(), *link));
				if (nand != nands.end()) {
					chain[0] = *link;
				} else {
					chain.push_back(node = *link);
				}
			}
		}
		chains.push_back(chain);
	}
	// print_chains(chains);
	return chains;
}

typedef std::queue<std::pair<std::string, PulseVector> > ProcessQueue;
static unsigned int	push_button(ModMap const &mods, StringVector const &nands)
{
	bool			flipped(false);
	std::string		src("button");
	Pulse			next(std::make_pair(src, false));
	PulseVector		pv(mods.find("broadcaster")->second->pulse(next));
	ProcessQueue	queue;

	queue.push(std::make_pair("broadcaster", pv));
	while(!queue.empty()) {
		src = queue.front().first;
		pv = queue.front().second;
		queue.pop();
		for (PulseVector::const_iterator pulse = pv.begin();
		pulse != pv.end(); ++pulse) {
			next = std::make_pair(src, pulse->second);
			ModMap::const_iterator	mod(mods.find(pulse->first));
			if (mod != mods.end()) {
				queue.push(std::make_pair(pulse->first,
				mod->second->pulse(next)));
				if (pulse->second) { continue; }
				for (size_t i = 4; i < nands.size() - 1; ++i) {
					if (nands[i] == pulse->first) {
						flipped = true;
					}
				}
			}
		}
	}
	return flipped;
}

size_t	turn_on_sand_machine(StringVector const &data)
{
	ModMap						modules(map_modules(data));
	StringVector				nands(sort_nands(modules, select_nands(data)));
	std::vector<StringVector>	links(link_latches(modules, nands));
	unsigned int				btn_presses(0U);
	std::vector<unsigned int>	cycles;

	while (++btn_presses < 1000000 && cycles.size() < 4) {
		if (push_button(modules, nands)) {
			cycles.push_back(btn_presses);
		}
	}
	size_t	res(*cycles.begin());
	for (std::vector<unsigned int>::const_iterator clock = cycles.begin() + 1;
	clock != cycles.end(); ++clock) {
		res = lcm(*clock, res);
	}
	cleanup(modules);
	return res;
}

size_t	gcd(size_t a, size_t b)
{
	if (!b || b == a)	return a;
	if (!a)				return b;
	if (a > b) {
		if (!(a % b))	return b;
		return gcd(a - b, b);
	}
	if (!(b % a))		return a;
	return gcd(a, b - a);
}

size_t	lcm(size_t a, size_t b)
{
	size_t	g(gcd(a, b));
	return ((a / g) * b);
}
