/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 06:07:24 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/13 09:35:00 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)					return 1;
	std::ifstream					file(av[1]);
	if (!file.is_open())			return 1;
	std::string						line;
	StringVector					lines;
	unsigned long int				res(0), res2(0);

	while (std::getline(file, line)) {
		if (line.empty()) {
			int n = get_reflection(lines) * 100;
			if (!n) {
				n = get_reflection(rotate(lines));
			}
			res += n;
			res2 += get_better_reflection(lines, false);
			lines.clear();
			continue;
		}
		lines.push_back(line);
	}
	file.close();
	if (!lines.empty()) {
		int n = get_reflection(lines) * 100;
		if (!n) {
			n = get_reflection(rotate(lines));
		}
		res += n;
		res2 += get_better_reflection(lines, false);
	}
	std::cout	<< "Result 1: "
				<< res
				<< std::endl;
	std::cout	<< "Result 2: "
				<< res2
				<< std::endl;
	return 0;
}

bool	unsmudge(std::string const &lin1, std::string const &lin2, bool &flip)
{
	flip = false;
	for (size_t i = 0; i < lin1.length(); ++i) {
		if (lin1[i] != lin2[i]) {
			if (flip)	return false;
			flip = true;
		}
	}
	return flip;
}

int	get_better_reflection(StringVector const &lines, bool rotated)
{
	for (size_t i = 0; i + 1 < lines.size(); ++i) {
		bool	fixed(false);
		if (lines[i] == lines[i + 1]
		|| unsmudge(lines[i], lines[i + 1], fixed)) {
			size_t j = 1;
			while ( j <= i && j + i + 1 < lines.size()) {
				if (lines[i - j] != lines[i + j + 1]
				&& (fixed || !unsmudge(lines[i - j], lines[i + j + 1], fixed)))
					break;
				++j;
			}
			if (fixed && (j > i || j + i + 1 == lines.size())) {
				return ((i + 1) * 100);
			}
		}
	}
	if (rotated)	return 0;
	return get_better_reflection(rotate(lines), true) / 100;
}

int	get_reflection(StringVector const &lines)
{
	for (size_t i = 0; i + 1 < lines.size(); ++i) {
		if (lines[i] == lines[i + 1]) {
			size_t j = 1;
			while ( j <= i && j + i + 1 < lines.size()
			&& lines[i - j] == lines[i + j + 1]) {
				++j;
			}
			if (j > i || j + i + 1 == lines.size()) {
				return (i + 1);
			}
		}
	}
	return 0;
}

StringVector	rotate(StringVector const &matrix)
{
	StringVector	rot;
	size_t			len(matrix.size());

	rot.reserve(matrix[0].length());
	for (size_t i = 0; i < matrix[0].length(); ++i) {
		std::string		row;
		row.reserve(len);
		for (size_t j = 0; j < len; ++j) {
			row.push_back(matrix[len - j - 1][i]);
		}
		rot.push_back(row);
	}
	return rot;
}
