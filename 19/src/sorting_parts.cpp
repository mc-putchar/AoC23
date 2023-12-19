/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_parts.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:52:21 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/19 18:52:21 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Workflow.hpp"

static std::vector<Part>	get_parts(StringVector const &p)
{
	std::vector<Part>	parts;

	parts.reserve(p.size());
	for (StringVector::const_iterator it = p.begin();
	it != p.end(); ++it) {
		std::vector<int>		params;
		std::string::size_type	pos(it->find('='));
		while (pos != std::string::npos) {
			params.push_back(std::atoi(&it->c_str()[pos + 1]));
			pos = it->find('=', pos + 1);
		}
		while (params.size() < 4) {
			params.push_back(0L);
		}
		parts.push_back(Part(params[0], params[1], params[2], params[3]));
	}
	return parts;
}

static Rule	get_rule(std::string const &rule, std::string::size_type dest)
{
	bool	less(rule[1] == '<');
	int		val(std::atoi(rule.c_str() + 2));

	return Rule(std::make_pair(rule[0], val), less, rule.substr(dest));
}

WorkMap	get_workflows(StringVector const &w)
{
	WorkMap								workflows;
	WorkMap::iterator					work;
	std::pair<WorkMap::iterator, bool>	ins;

	for (StringVector::const_iterator it = w.begin();
	it != w.end(); ++it) {
		std::string				rule;
		std::stringstream		stream(*it);
		std::string::size_type	pos(it->find('{'));
		std::string				flowname(it->substr(0, pos++));
		ins = workflows.insert(std::make_pair(flowname, Workflow(flowname)));
		if (!ins.second)		{ continue; }
		work = ins.first;
		stream.seekg(pos);
		while (std::getline(stream, rule, ',')) {
			pos = rule.find(':');
			if (pos == std::string::npos) {
				work->second.set_final(rule.substr(0, rule.length() - 1));
				break;
			}
			if (rule.length() > 4) {
				work->second.add_rule(get_rule(rule, ++pos));
			}
		}
	}
	return workflows;
}

unsigned long int	organize(StringVector const &p, StringVector const &w)
{
	std::vector<Part>	parts(get_parts(p));
	WorkMap				workmap(get_workflows(w));
	unsigned long int	acc(0);

	WorkMap::const_iterator	workstart(workmap.find("in")), next;
	workmap.insert(std::make_pair("A", Workflow("A")));
	workmap.insert(std::make_pair("R", Workflow("R")));
	for (std::vector<Part>::const_iterator part = parts.begin();
	part != parts.end(); ++part) {
		// std::cout << "{" << *part << "}" << std::endl;
		next = workmap.find(workstart->second.process(*part));
		while (next != workmap.end() && next->first.compare("R")) {
			// std::cout << "Next: " << next->first << std::endl;
			if (!next->first.compare("A")) {
				// std::cout << "Accepted: " << *part << std::endl;
				acc += part->rate();
				break;
			}
			next = workmap.find(next->second.process(*part));
		}
	}
	return acc;
}
