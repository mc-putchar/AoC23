/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:26:51 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/14 11:26:51 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"

namespace {
	static int const	k_ncycles = 1000000000;
}

int	main(int ac, char **av)
{
	if (ac != 2)				return 1;
	std::ifstream				file(av[1]);
	if (!file.is_open())		return 1;
	std::string					line;
	StringVector				platform;

	while (std::getline(file, line) && !line.empty()) {
		platform.push_back(line);
	}
	file.close();
	StringVector				platform_copy(platform);
	tilt_north(platform);
	std::cout	<< "Result 1: "
				<< calculate_load(platform)
				<< std::endl;
	std::cout	<< "Result 2: "
				<< spin_cycle(platform_copy, k_ncycles)
				<< std::endl;
	return 0;
}

void	tilt_north(StringVector &platform)
{
	for (size_t i = 0; i < platform[0].length(); ++i) {
		size_t	top(0);
		for (size_t j = 0; j < platform.size(); ++j) {
			switch (platform[j][i]) {
				case 'O': 
					if (top != j)
						std::swap(platform[j][i], platform[top][i]);
					++top;
					break;
				case '#':
					top = j + 1;
				case '.':
				default:	break;
			}
		}
	}
}

void	tilt_south(StringVector &platform)
{
	for (size_t i = 0; i < platform[0].length(); ++i) {
		size_t	top(platform.size() - 1);
		for (size_t j = platform.size(); j > 0; --j) {
			switch (platform[j - 1][i]) {
				case 'O': 
					if (top != j - 1)
						std::swap(platform[j - 1][i], platform[top][i]);
					--top;
					break;
				case '#':
					top = j - 2;
				case '.':
				default:	break;
			}
		}
	}
}

void	tilt_west(StringVector &platform)
{
	for (size_t j = 0; j < platform.size(); ++j) {
		size_t	top(0);
		for (size_t i = 0; i < platform[0].length(); ++i) {
			switch (platform[j][i]) {
				case 'O': 
					if (top != i)
						std::swap(platform[j][i], platform[j][top]);
					++top;
					break;
				case '#':
					top = i + 1;
				case '.':
				default:	break;
			}
		}
	}
}

void	tilt_east(StringVector &platform)
{
	for (size_t j = 0; j < platform.size(); ++j) {
		size_t	top(platform[j].length() - 1);
		for (size_t i = platform[j].length(); i > 0; --i) {
			switch (platform[j][i - 1]) {
				case 'O': 
					if (top != i - 1)
						std::swap(platform[j][i - 1], platform[j][top]);
					--top;
					break;
				case '#':
					top = i - 2;
				case '.':
				default:	break;
			}
		}
	}
}

int	calculate_load(StringVector &platform)
{
	int		load(0);
	size_t	size(platform.size());

	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < platform[i].length(); ++j) {
			if (platform[i][j] == 'O') {
				load += size - i;
			}
		}
	}
	return load;
}

static bool	find_period(std::vector<StringVector> const &patterns, \
	int const &i, int &period, int &offset)
{
	int	x(0);

	while (!period && x < i) {
		if (patterns[x] != patterns[i]) {
			++x;
			continue;
		}
		int	s(x);
		while (!period && ++s < i) {
			if (patterns[x] == patterns[s]) {
				int	q(x);
				int	t(s);
				++period;
				while (++q < s && ++t < i && patterns[q] == patterns[t]) {
					++period;
				}
				if (q != s) {
					period = 0;
				} else {
					int	w(i);
					while (w > s && patterns[w] == patterns[w - period])
						--w;
					if (w != s) {
						period = 0;
					} else {
						offset = x;
						return true;
					}
				}
			}
		}
		++x;
	}
	return false;
}

int	spin_cycle(StringVector &platform, int n)
{
	std::vector<StringVector>	patterns;
	int							offset(0), period(0);

	for (int i = 0; i < n; ++i) {
		tilt_north(platform);
		tilt_west(platform);
		tilt_south(platform);
		tilt_east(platform);
		patterns.push_back(platform);
		if (i > 1000 && find_period(patterns, i, period, offset))
			return calculate_load(patterns[offset + ((n - 1) % period)]);
	}
	return calculate_load(platform);
}
