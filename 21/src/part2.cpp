/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 07:09:42 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/21 07:09:42 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"

static unsigned long int	get_fill_value(StringVector lines, int steps)
{
	unsigned long int	count(0);

	while (steps--) {
		lines = simulate(lines);
	}
	for (StringVector::const_iterator line = lines.begin();
	line != lines.end(); ++line) {
		count += std::count(line->begin(), line->end(), 'O');
	}
	return count;
}

static unsigned long int	get_corners(StringVector lines, int n)
{
	unsigned long int	count(0);
	lines[0][0] = 'O';
	count += get_fill_value(lines, n);
	lines[0][0] = '.';
	lines[0][lines[0].length() - 1] = 'O';
	count += get_fill_value(lines, n);
	lines[0][lines[0].length() - 1] = '.';
	lines[lines.size() - 1][0] = 'O';
	count += get_fill_value(lines, n);
	lines[lines.size() - 1][0] = '.';
	lines[lines.size() - 1][lines[0].length() - 1] = 'O';
	count += get_fill_value(lines, n);
	lines[lines.size() - 1][lines[0].length() - 1] = '.';
	return (count);
}

static unsigned long int	get_edges(StringVector lines)
{
	unsigned long int	count(0);
	size_t				len(lines.size());

	lines[0][len >> 1] = 'O';
	count += get_fill_value(lines, len - 1);
	lines[0][len >> 1] = '.';
	lines[len >> 1][0] = 'O';
	count += get_fill_value(lines, len - 1);
	lines[len >> 1][0] = '.';
	lines[len >> 1][len - 1] = 'O';
	count += get_fill_value(lines, len - 1);
	lines[len >> 1][len - 1] = '.';
	lines[len - 1][len >> 1] = 'O';
	count += get_fill_value(lines, len - 1);
	return (count);
}

/* Assumptions and observations:
 * start is at the center of square grid of odd dimensions
 * grid has outer frame of dots as well as inner diamond of dots (quatergonals?)
 * clear LOS from start to parallel starts in each direction
 * approximate linear rhomboid spread (quadratic area) despite obstacles
 * steps % grid length == grid length / 2 (exactly to edge)
 * 
 * O - starting filled; X - opposite filled;
 * q - corner (~1/8); s - chipped at corner (~7/8); e - edge fill (~3/4)
 *  O       X       q       s       e
 * 0.0.0   .0.0.   .0...   ..0.0   ..0.0
 * .0.0.   0.0.0   0....   .0.0.   .0.0.
 * 0.0.0   .0.0.   .....   0.0.0   0.0.0
 * .0.0.   0.0.0   .....   .0.0.   .0.0.
 * 0.0.0   .0.0.   .....   0.0.0   ..0.0
 * 
 * .......   ...qeq...
 * ..qeq..   ..qsXsq..
 * .qsXsq.   .qsXOXsq.
 * .eXOXe.   .eXOXOXe.
 * .qsXsq.   .qsXOXsq.
 * ..qeq..   ..qsXsq..
 * .......   ...qeq...
 * 
 * ==> 4e + 8q + 4s + 1O + 4X
 * ===> 4e + 12q + 8s + 4O + 9X
 * 
 * generally, for n, where n=floor(steps / grid length)
 * PS => 4e + n*4q + (n-1)*4s
 * FS => n^2 * X + (n-1)^2 * O
 * PS(partial squares) + FS(full squares)
 * I guess, maybe, wtf do I know
 */
unsigned long int	count_parallel(StringVector lines, int steps)
{
	unsigned int			n(steps / lines.size());
	unsigned long int		filled, opposite, corners, chipped;
	unsigned long long int	count(0);
	size_t	r(0), c(0);

	for ( ; r < lines.size(); ++r) {
		for (c = 0; c < lines[r].length(); ++c) {
			if (lines[r][c] == 'S') {
				lines[r][c] = '.';
				break;
			}
		}
		if (c < lines[r].length()) { break; }
	}
	count += get_edges(lines);
	corners = get_corners(lines, (lines.size() >> 1) - 1);
	chipped = get_corners(lines, lines.size() + (lines.size() >> 1) - 1);
	count += corners * n;
	count += chipped * (n - 1);
	lines[r][c] = 'O';
	filled = get_fill_value(lines, lines.size() << 1);
	opposite = get_fill_value(lines, (lines.size() << 1) + 1);
	count += (filled * n * n);
	--n;
	count += (opposite * n * n);
	return count;
}
