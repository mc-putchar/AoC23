/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 07:04:12 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/22 07:04:12 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Brick.hpp"

void	settle_down(std::vector<Brick> &slabs)
{
	int	h(0);

	std::sort(slabs.begin(), slabs.end());
	while (++h <= slabs.rbegin()->top()) {
		for (std::vector<Brick>::iterator slab = slabs.begin();
		slab != slabs.end(); ++slab) {
			if (h >= slab->bottom()) { continue; }
			int	drop_h(-1);
			for (std::vector<Brick>::const_iterator it = slabs.begin();
			it != slab; ++it) {
				if (it->intersects(*slab)
				&& (drop_h == -1
				|| drop_h > slab->bottom() - it->top() - 1)) {
					drop_h = slab->bottom() - it->top() - 1;
				}
			}
			if (drop_h == -1) {
				drop_h = slab->bottom() - 1;
			}
			slab->drop(drop_h);
		}
	}
}

static std::vector<unsigned int>	calc_supports(std::vector<Brick> const &sls)
{
	std::vector<unsigned int>	supps;

	for (std::vector<Brick>::const_reverse_iterator slab = sls.rbegin();
	slab != sls.rend(); ++slab) {
		unsigned int	supports(0U);
		for (std::vector<Brick>::const_reverse_iterator it = slab + 1;
		it != sls.rend(); ++it) {
			if (it->top() == slab->bottom() - 1 && it->intersects(*slab)) {
				++supports;
			}
		}
		supps.push_back(supports);
	}
	std::reverse(supps.begin(), supps.end());
	return supps;
}

unsigned int	disintegration_targets(std::vector<Brick> const &slabs)
{
	unsigned int				count(0U);
	std::vector<unsigned int>	supports;

	supports = calc_supports(slabs);
	for (size_t i = 0; i < slabs.size(); ++i) {
		bool	removable(true);
		int		h(slabs[i].top() + 1);
		for (size_t j = 0; j < slabs.size(); ++j) {
			if (j == i || slabs[j].bottom() != h
			|| !slabs[j].intersects(slabs[i])) { 
				continue;
			}
			if (supports[j] < 2) {
				removable = false;
				break;
			}
		}
		if (removable) {
			++count;
		}
	}
	return count;
}
