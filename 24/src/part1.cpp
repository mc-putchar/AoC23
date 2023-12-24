/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 06:51:41 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/24 06:51:41 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Ray.hpp"

namespace {
	/* test case values */
	// static size_t const	k_min = 7U;
	// static size_t const	k_max = 27U;
	/* actual input values */
	static long long int const	k_min = 200000000000000U;
	static long long int const	k_max = 400000000000000U;
}

std::vector<Ray>	parse_input(StringVector const &input)
{
	std::vector<Ray>	rays;

	rays.reserve(input.size());
	for (StringVector::const_iterator in = input.begin();
	in != input.end(); ++in) {
		size_t				px, py, pz;
		int					vx, vy, vz;
		std::istringstream	iss(*in);
		iss >> px; iss.ignore();
		iss >> py; iss.ignore();
		iss >> pz; iss.ignore();
		iss.ignore();
		iss >> vx; iss.ignore();
		iss >> vy; iss.ignore();
		iss >> vz; iss.ignore();
		rays.push_back(Ray(Point3L(px, py, pz), Point3(vx, vy, vz)));
	}
	return rays;
}

unsigned int	count_intersections(StringVector const &input)
{
	std::vector<Ray>	rays(parse_input(input));
	unsigned int		n_xs(0U);

	for (size_t i = 0; i < rays.size() - 1; ++i) {
		for (size_t j = i + 1; j < rays.size(); ++j) {
			if (rays[i].intersects(rays[j], k_min, k_max)) {
				// std::cout << "Ray " << i + 1 << " intersects with ray "
				// << j + 1 << std::endl;
				++n_xs;
			}
		}
	}
	return n_xs;
}
