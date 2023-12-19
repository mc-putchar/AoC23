/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_mode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:56:03 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/19 18:56:03 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Workflow.hpp"

static void	push_inverted(std::vector<Match> const &match_vector,
				std::stack<Match> &stack)
{
	for (std::vector<Match>::const_reverse_iterator it = match_vector.rbegin();
	it != match_vector.rend(); ++it) {
		stack.push(*it);
	}
}

static void	include(uint32_t lim, u_rating &comblo, u_rating &combhi)
{
	unsigned char			off(lim & 3);
	t_rating				hi(lim >> 2);
	if (hi < combhi.x[off])	{ combhi.x[off] = hi; }
	t_rating				lo(lim >> 18);
	if (lo > comblo.x[off])	{ comblo.x[off] = lo; }
}

static void	exclude(uint32_t lim, u_rating &comblo, u_rating &combhi)
{
	unsigned char	off(lim & 3);
	t_rating		lo(lim >> 18);
	t_rating		hi(lim >> 2);
	if (lo) {
		if (++lo < combhi.x[off])	{ combhi.x[off] = lo; }
		return;
	}
	if (--hi > comblo.x[off]) {
		comblo.x[off] = hi;
	}
}

static std::vector<u_rating>	filter(MatchMap const &workmap)
{
	std::vector<u_rating>		accepted;
	Match						match;
	u_rating					comb[2];
	u_rating					next[2];
	std::stack<Match>			pending;
	std::stack<u_rating>		combstack;

	comb[0].total = 0U;
	comb[1].total = (4001ULL << 48) | (4001ULL << 32) | (4001U << 16) | 4001U;
	combstack.push(comb[1]);
	combstack.push(comb[0]);
	push_inverted((workmap.find("in"))->second, pending);
	while (!pending.empty()) {
		match = pending.top(); pending.pop();
		comb[0] = combstack.top(); combstack.pop();
		comb[1] = combstack.top(); combstack.pop();
		next[0] = comb[0]; next[1] = comb[1];
		if (!match.second.compare("A")) {
			if (match.first) {
				include(match.first, comb[0], comb[1]);
			}
			accepted.push_back(comb[0]);
			accepted.push_back(comb[1]);
		}
		if (!match.first) {
			if (match.second.compare("R") && match.second.compare("A")) {
				push_inverted((workmap.find(match.second))->second, pending);
				combstack.push(comb[1]);
				combstack.push(comb[0]);
			}
			continue;
		}
		exclude(match.first, next[0], next[1]);
		combstack.push(next[1]);
		combstack.push(next[0]);
		if (match.second.compare("R") && match.second.compare("A")) {
			include(match.first, comb[0], comb[1]);
			if (comb[0] < comb[1]) {
				push_inverted((workmap.find(match.second))->second, pending);
				combstack.push(comb[1]);
				combstack.push(comb[0]);
			}
		}
	}
	return accepted;
}

unsigned long long int	summarize(WorkMap const &workmap)
{
	MatchMap					wfmap;

	for (WorkMap::const_iterator wf = workmap.begin();
	wf != workmap.end(); ++wf) {
		wfmap.insert(std::make_pair(wf->first, wf->second.summarize()));
	}

	unsigned long long int		count(0);
	std::vector<u_rating>		combs(filter(wfmap));
	u_rating					lo;
	u_rating					hi;
	for (std::vector<u_rating>::const_iterator it = combs.begin();
	it != combs.end(); ) {
		lo = *it++;
		hi = *it++;
		if (lo < hi) {
			count += static_cast<uint64_t>
				((hi.x[0] - lo.x[0] - 1))
				* (hi.x[1] - lo.x[1] - 1)
				* (hi.x[2] - lo.x[2] - 1)
				* (hi.x[3] - lo.x[3] - 1);
		}
	}
	return count;
}
