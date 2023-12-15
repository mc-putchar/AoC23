/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:46:58 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/15 00:52:04 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Stopwatch.hpp"
#include "Utils.hpp"

namespace {
	static size_t const	k_batch_size = 10;
}

int	main(int ac, char **av)
{
	if (ac != 2)					return 1;
	std::ifstream					file(av[1]);
	if (!file.is_open())			return 1;
	std::string						line;
	std::vector<Row>				rows;
	int								res(0);

	while (std::getline(file, line) && !line.empty()) {
		std::vector<int>	groups;
		std::string			row(analyze(line, groups));
		rows.push_back(std::make_pair(row, groups));
		res += backtrack(row, groups,
				std::accumulate(groups.begin(), groups.end(), 0));
	}
	file.close();
	std::cout	<< "Result 1: "
				<< res
				<< std::endl;
	std::cout	<< "Result 2: "
				<< accumulate_futures(rows)
				<< std::endl;
	return 0;
}

unsigned long int	accumulate_futures(std::vector<Row> &rows)
{
	unsigned long int	acc(0);
	FutureVector		futures;
	size_t				total(rows.size());
	size_t				counter(0);
	Stopwatch			time;

	futures.reserve(k_batch_size + 1);
	for (std::vector<Row>::const_iterator row = rows.begin();
	row != rows.end();) {
		if (++counter > k_batch_size)	break;
		std::vector<int>	groups;
		std::string			data(unfold(row->first, row->second, groups));
		futures.push_back(std::async(
			std::launch::async,
			backtrack, data, groups,
			std::accumulate(groups.begin(), groups.end(), 0)));
		row = rows.erase(row);
	}
	counter = 0;
	while (!futures.empty()) {
		std::cout << "[";
		for (FutureVector::iterator task = futures.begin();
		task != futures.end();) {
			std::future_status	stat(task->wait_for(
								std::chrono::milliseconds(1000)));
			if (stat == std::future_status::timeout) {
				std::cout << "=" << std::flush;
				std::advance(task, 1);
			} else {
				acc += task->get();
				++counter;
				if (!rows.empty()) {
					std::vector<Row>::iterator row(rows.begin());
					futures.push_back(std::async(
						std::launch::async,
						backtrack, row->first, row->second,
						std::accumulate(
							row->second.begin(), row->second.end(), 0)));
					row = rows.erase(row);
				}
				task = futures.erase(task);
			}
		}
		std::cout	<< "]\nDone: " << counter
					<< " / " << total << std::endl;
		time.elapsed();
	}
	return acc;
}

std::string	analyze(std::string const &line, std::vector<int> &groups)
{
	std::string::size_type				pos(line.find(' '));
	if (pos == std::string::npos)		return "";
	std::vector<std::string>			nums(ft_splitstr(&line[pos + 1], ","));

	for (std::vector<std::string>::iterator num = nums.begin();
	  num != nums.end(); ++num) {
		int	n;
		std::istringstream(*num) >> n;
		groups.push_back(n);
	}
	return line.substr(0, pos);
}

static inline bool	accept(std::string const &comb, std::vector<int> const &groups)
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

static inline bool	reject(std::string const &comb, std::vector<int> const &groups, int n)
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

int	backtrack(std::string const &row, std::vector<int> const &groups, \
	size_t const &acc)
{
	if (reject(row, groups, acc)) {
		return 0;
	}
	std::string::size_type	pos(row.find('?'));
	if (pos == std::string::npos) { return accept(row, groups); }

	int			count(0);
	std::string	cand(row);
	cand[pos] = '#';
	count += backtrack(cand, groups, acc);
	cand[pos] = '.';
	return count + backtrack(cand, groups, acc);
}

std::string	unfold(std::string const &row, std::vector<int> const &groups,
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
