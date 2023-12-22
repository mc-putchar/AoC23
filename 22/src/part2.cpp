/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:25:21 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/22 11:25:21 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Brick.hpp"

typedef std::vector<std::vector<size_t> >	SupportVector;
static SupportVector	get_supports(std::vector<Brick> const &slabs)
{
	SupportVector	support_vectors;

	for (std::vector<Brick>::const_reverse_iterator slab = slabs.rbegin();
	slab != slabs.rend(); ++slab) {
		std::vector<size_t>	supports;
		for (std::vector<Brick>::const_reverse_iterator it = slab + 1;
		it != slabs.rend(); ++it) {
			if (it->top() == slab->bottom() - 1 && it->intersects(*slab)) {
				supports.push_back(
					slabs.size() - 1 - std::distance(slabs.rbegin(), it));
			}
		}
		support_vectors.push_back(supports);
	}
	std::reverse(support_vectors.begin(), support_vectors.end());
	return support_vectors;
}

static SupportVector	translate(SupportVector const &sv)
{
	SupportVector	supports(sv.size(), std::vector<size_t>());

	for (size_t i = 0; i < sv.size(); ++i) {
		for (std::vector<size_t>::const_iterator it = sv[i].begin();
		it != sv[i].end(); ++it) {
			supports[*it].push_back(i);
		}
	}
	return supports;
}

static bool	no_support(std::vector<size_t> const &supported_by,
						std::vector<bool> const &fallen)
{
	for (std::vector<size_t>::const_iterator it = supported_by.begin();
	it != supported_by.end(); ++it) {
		if (!fallen[*it]) {
			return false;
		}
	}
	return true;
}

static unsigned int	measure_reaction(std::vector<Brick> const &slabs,
									size_t removed,
									SupportVector const &supv,
									SupportVector const &sup_by,
									std::vector<bool> &fallen)
{
	unsigned int		count(0U);
	std::queue<size_t>	queue;

	if (supv[removed].empty()) { return 0U; }
	fallen[removed] = true;
	for (std::vector<size_t>::const_iterator it = supv[removed].begin();
	it != supv[removed].end(); ++it) {
		if (sup_by[*it].size() < 2 || no_support(sup_by[*it], fallen)) {
			++count;
			queue.push(*it);
		}
	}
	while (!queue.empty()) {
		size_t	next(queue.front()); queue.pop();
		count += measure_reaction(slabs, next, supv, sup_by, fallen);
	}
	return count;
}

unsigned long int	chain_reaction(std::vector<Brick> const &slabs)
{
	unsigned long int	count(0U);
	SupportVector		supported_by(get_supports(slabs));
	SupportVector		support_vectors(translate(supported_by));

	for (size_t i = 0; i < slabs.size(); ++i) {
		std::vector<bool>	fallen(slabs.size(), false);
		count += measure_reaction(slabs, i, support_vectors,
				supported_by, fallen);
	}
	return count;
}
