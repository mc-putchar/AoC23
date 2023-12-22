/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task1.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:50:52 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/20 10:50:52 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Module.hpp"

ModMap	map_modules(StringVector const &data)
{
	ModMap			modules;
	StringVector	nands;

	for (StringVector::const_iterator it = data.begin();
	it != data.end(); ++it) {
		std::istringstream	iss(*it);
		std::string			tmp;
		Module				*mod;

		iss >> tmp;
		switch (tmp[0]) {
		case '%':	mod = new Flipflop(); 
					tmp.erase(0, 1);
					break;
		case '&':	mod = new Conjunction();
					tmp.erase(0, 1);
					nands.push_back(tmp);
					break;
		default:	mod = new Broadcaster();
					break;
		}
		modules.insert(std::make_pair(tmp, mod));
		iss >> tmp >> tmp;
		while (tmp[tmp.length() - 1] == ',') {
			mod->add_output(tmp.substr(0, tmp.length() - 1));
			iss >> tmp;
		}
		mod->add_output(tmp);
	}
	for (StringVector::const_iterator it = nands.begin();
	it != nands.end(); ++it) {
		Module	*con(modules.find(*it)->second);
		for (ModMap::iterator mod = modules.begin();
		mod != modules.end(); ++mod) {
			if (con != mod->second && mod->second->has_dest(*it)) {
				dynamic_cast<Conjunction *>(con)->register_input(mod->first);
			}
		}
	}
	return modules;
}

void	cleanup(ModMap	&modules)
{
	for (ModMap::iterator it = modules.begin();
	it != modules.end(); ++it) {
		delete it->second;
	}
}

void	print_modules(ModMap const &modules)
{
	for (ModMap::const_iterator it = modules.begin();
	it != modules.end(); ++it) {
		std::cout << it->first << " -> ";
		for (StringVector::const_iterator d = it->second->dest().begin();
		d != it->second->dest().end(); ++d) {
			std::cout << *d << ", ";
		}
		std::cout << std::endl;
	}
}

static void	push_button(ModMap const &modules,
	unsigned int &lo, unsigned int &hi)
{
	std::string						src("button");
	Pulse							next(std::make_pair(src, false));
	PulseVector						pv(modules.find("broadcaster")
									->second->pulse(next));
	std::queue<std::pair<std::string, PulseVector> >
		queue;

	++lo;
	queue.push(std::make_pair("broadcaster", pv));
	while(!queue.empty()) {
		src = queue.front().first;
		pv = queue.front().second;
		queue.pop();
		for (PulseVector::const_iterator pulse = pv.begin();
		pulse != pv.end(); ++pulse) {
			pulse->second ? ++hi : ++lo;
			// std::cout << "Pulse: " << src << (pulse->second ? " +" : " -")
			// 	<< " -> " << pulse->first << std::endl;
			next = std::make_pair(src, pulse->second);
			ModMap::const_iterator	mod(modules.find(pulse->first));
			if (mod != modules.end()) {
				queue.push(std::make_pair(pulse->first,
				mod->second->pulse(next)));
			}
		}
	}
}

unsigned int	propagation_product(StringVector const &data)
{
	ModMap			modules(map_modules(data));
	unsigned int	lo(0), hi(0);

	for (int i = 0; i < 1000; ++i) {
		push_button(modules, lo, hi);
	}
	cleanup(modules);
	return (lo * hi);
}
