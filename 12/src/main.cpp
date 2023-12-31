/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 04:08:29 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/18 14:12:33 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Utils.hpp"

namespace {
	Cache	memo;
}

int	main(int ac, char **av)
{
	if (ac != 2)					return 1;
	std::ifstream					file(av[1]);
	if (!file.is_open())			return 1;
	std::string						line;
	std::vector<Row>				rows;
	int								res(0);
	unsigned long int				res2(0);

	while (std::getline(file, line) && !line.empty()) {
		std::vector<int>	groups;
		std::string			row(analyze(line, groups));
		rows.push_back(std::make_pair(row, groups));
	}
	file.close();
	for (std::vector<Row>::const_iterator it = rows.begin();
	it != rows.end(); ++it) {
		res += dynamic(*it);
	}
	std::cout	<< "Result 1: "
				<< res
				<< std::endl;
	for (std::vector<Row>::const_iterator it = rows.begin();
	it != rows.end(); ++it) {
		res2 += dynamic(unfold(*it));
	}
	std::cout	<< "Result 2: "
				<< res2
				<< std::endl;
	return 0;
}

std::string	analyze(std::string const &line, std::vector<int> &groups)
{
	std::string::size_type	pos(line.find(' '));
	if (pos == std::string::npos
	|| pos + 1 >= line.length()) {
		return "";
	}
	std::vector<std::string>	nums(ft_splitstr(&line[pos + 1], ","));

	for (std::vector<std::string>::iterator num = nums.begin();
	  num != nums.end(); ++num) {
		int	n;
		std::istringstream(*num) >> n;
		groups.push_back(n);
	}
	return line.substr(0, pos);
}

static bool	accept(std::string const &comb, std::vector<int> const &groups)
{
	std::string::size_type	pos(0);

	for (std::vector<int>::const_iterator it = groups.begin();
	it != groups.end(); ++it) {
		pos = comb.find('#', pos);
		if (pos == std::string::npos
		|| (pos && comb[pos - 1] != '.')
		|| (pos + *it < comb.length() && comb[pos + *it] != '.')
		|| pos + *it > comb.length()) {
			return false;
		}
		for (int i = 1; i < *it; ++i) {
			if (comb[pos + i] != '#') {
				return false;
			}
		}
		pos += *it;
	}
	pos = comb.find('#', pos);
	return (pos == std::string::npos);
}

static bool	reject(std::string const &comb,
			std::vector<int> const &groups, int n)
{
	size_t	len(comb.length());
	if (static_cast<int>(len) - n < std::count(comb.begin(), comb.end(), '.')
	|| n < std::count(comb.begin(), comb.end(), '#')) {
		return true;
	}
	std::string::size_type	pos(0);
	std::string::size_type	q(comb.find('?'));
	for (std::vector<int>::const_iterator it = groups.begin();
	it != groups.end(); ++it) {
		pos = comb.find('#', pos);
		if (pos == std::string::npos || pos + *it >= q)	return false;
		if ((pos && comb[pos - 1] == '#')
		|| (pos + *it < comb.length() && comb[pos + *it] == '#')
		|| pos + *it > comb.length()) {
			return true;
		}
		for (int i = 1; i < *it; ++i) {
			if (comb[pos + i] == '.') {
				return true;
			}
		}
		pos += *it;
	}
	return false;
}

unsigned long int	backtrack(std::string const &row,
					std::vector<int> const &groups,
					size_t const &acc)
{
	if (reject(row, groups, acc))	{ return 0; }
	std::string::size_type	pos(row.find('?'));
	if (pos == std::string::npos)	{ return accept(row, groups); }

	unsigned long int	count(0);
	std::string			cand(row);
	cand[pos] = '#';
	count += backtrack(cand, groups, acc);
	cand[pos] = '.';
	return count + backtrack(cand, groups, acc);
}

std::string	unfold(std::string const &row,
			std::vector<int> const &groups,
			std::vector<int> &unfolded_groups)
{
	std::ostringstream	unfolded_row;
	unfolded_groups.reserve(groups.size() * 5);
	for (int i = 0; i < 5; ++i) {
		for (std::vector<int>::const_iterator it = groups.begin();
		it != groups.end(); ++it) {
			unfolded_groups.push_back(*it);
		}
		if (i) {
			unfolded_row << "?";
		}
		unfolded_row << row;
	}
	return unfolded_row.str();
}

Row	unfold(Row const &row)
{
	std::vector<int>	un_groups;
	std::string			un_row(unfold(row.first, row.second, un_groups));
	return std::make_pair(un_row, un_groups);
}

unsigned long int	subdivide(std::string const &seq,
				std::vector<int> const &groups)
{
	if (groups.empty() || !groups[0]) {
		return (seq.find('#') == std::string::npos ? 1 : 0);
	}
	Cache::iterator	hit(memo.find(std::make_pair(seq, groups)));
	if (hit != memo.end()) {
		return hit->second;
	}
	if (groups.size() < 3) {
		unsigned long int	r = backtrack(seq, groups,
			std::accumulate(groups.begin(), groups.end(), 0));
		memo.insert(std::make_pair(std::make_pair(seq, groups), r));
		return r;
	}
	std::vector<int>		subgroup1(groups.begin(), groups.begin() + 2);
	std::vector<int>		subgroup2(groups.begin() + 2, groups.end());
	std::string::size_type	mark(subgroup1[0] + subgroup1[1] + 1);
	unsigned long int		iter(0), count (0);
	while (mark != std::string::npos) {
		while (mark < seq.length()
		&& (seq[mark] == '#' || seq[mark - 1] == '.')) {
			++mark;
		}
		if (seq.length() - mark <= std::accumulate(subgroup2.begin(),
								subgroup2.end(), subgroup2.size() - 1)) {
			memo.insert(std::make_pair(std::make_pair(seq, groups), count));
			return count;
		}
		std::string	sub(seq.substr(0, mark));
		if (iter && sub[mark - 1] == '?') {
			sub[mark - 1] = '#';
		}
		unsigned long int	first(subdivide(sub, subgroup1));
		if (first && mark + 1 < seq.length()) {
			unsigned long int	sec(subdivide(seq.substr(mark + 1), subgroup2));
			count += first * sec;
		}
		++iter;
		mark = seq.find_first_not_of('#', mark + 1);
	}
	memo.insert(std::make_pair(std::make_pair(seq, groups), count));
	return count;
}

unsigned long int	dynamic(Row const &row)
{
	return subdivide(row.first, row.second);
}
