/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:42:30 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/05 10:42:30 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Utils.hpp"

typedef unsigned int										uint32_t;
typedef std::vector<std::string>::iterator					vectit;
typedef std::map<uint32_t, std::pair<uint32_t, uint32_t> >	ConTable;
typedef std::pair<uint32_t, uint32_t>						Range;
typedef ConTable::const_iterator							ConIt;

static bool	get_seeds(std::string const &line, std::vector<uint32_t> &seedv)
{
	std::string::size_type		pos;
	std::vector<std::string>	nums;

	pos = line.find(":");
	if (pos == std::string::npos)	return false;
	nums = ft_splitstr(&line[pos + 1], " ");
	for (vectit it = nums.begin(); it != nums.end(); ++it) {
		std::istringstream	iss;
		uint32_t			num;
		iss.str(*it);
		iss >> num;
		if (iss.fail())	continue;
		seedv.push_back(num);
	}
	return (!seedv.empty());
}

static bool	get_seed_range(std::string const &line, std::vector<Range> &seedv)
{
	std::string::size_type		pos;
	std::vector<std::string>	nums;

	pos = line.find(":");
	if (pos == std::string::npos)	return false;
	nums = ft_splitstr(&line[pos + 1], " ");
	if (nums.size() & 1)			return false;
	for (vectit it = nums.begin(); it != nums.end(); ++it) {
		uint32_t			num, range;
		std::istringstream(*it++) >> num;
		std::istringstream(*it) >> range;
		seedv.push_back(std::make_pair(num, range));
	}
	return (!seedv.empty());
}

static bool	get_con_table(std::vector<std::string> lines, ConTable &table)
{
	for (vectit it = lines.begin(); it != lines.end(); ++it) {
		if ((*it).empty())
			return (!table.empty());
		std::vector<std::string>	nums = ft_splitstr(*it, " ");
		if (nums.size() < 3) {
			std::cout << "Invalid data entry" << std::endl;
			continue;
		}
		uint32_t	dest, src, range;
		std::istringstream(nums[0]) >> dest;
		std::istringstream(nums[1]) >> src;
		std::istringstream(nums[2]) >> range;
		if (!(table.insert(std::make_pair(src, std::make_pair(range, dest)))).second) {
			std::cout << "Conversion table error\n";
			continue;
		}
	}
	return true;
}

static void	convert_values(std::vector<uint32_t> &values, ConTable const &table)
{
	for (std::vector<uint32_t>::iterator val = values.begin(); val != values.end(); ++val) {
		ConIt	con(table.upper_bound(*val));

		if (con == table.begin())	continue;
		--con;
		if (con->first + con->second.first > *val)
			*val = con->second.second + (*val - con->first);
	}
}

static void	convert_ranges(std::vector<Range> &ranges, ConTable const &table)
{
	std::vector<Range>	converted;

	for (std::vector<Range>::iterator seed = ranges.begin(); seed != ranges.end();) {
		bool	itValid(true);
		for (ConIt con = table.begin(); con != table.end(); ++con) {
			uint32_t const	src = con->first;
			uint32_t const	range = con->second.first;
			uint32_t		start(src);
			uint32_t		span(0);
			uint32_t		tmp(0);

			if (src + range <= seed->first || src >= seed->first + seed->second)
				continue;
			if (src < seed->first)
				start = seed->first;
			if (src + range < seed->first + seed->second)
				span = src + range - start;
			else
				span = seed->first + seed->second - start;
			converted.push_back(std::make_pair(start - src + con->second.second, span));

			if (seed->first < start) {
				tmp = seed->second;
				seed->second = start - seed->first;
				if (start + span < seed->first + tmp) {
					ranges.push_back(std::make_pair(start + span, seed->first + tmp - start - span));
					itValid = false;
				}
			}
			else if (start + span < seed->first + seed->second) {
				tmp = seed->first;
				seed->first = start + span;
				seed->second = tmp + seed->second - seed->first;
			}
			else {
				ranges.erase(seed);
				itValid = false;
			}
		}
		if (itValid)
			std::advance(seed, 1);
		else
			seed = ranges.begin();
	}
	if (!converted.empty())
		ranges.insert(ranges.end(), converted.begin(), converted.end());
}

static uint32_t	find_min(std::vector<Range> const &ranges)
{
	uint32_t	min(ranges.begin()->first);
	for (std::vector<Range>::const_iterator it = ranges.begin(); it != ranges.end(); ++it) {
		if (it->first < min)
			min = it->first;
	}
	return (min);
}

static const std::string mappings[] = \
{
	"seed-to-soil map:",
	"soil-to-fertilizer map:",
	"fertilizer-to-water map:",
	"water-to-light map:",
	"light-to-temperature map:",
	"temperature-to-humidity map:",
	"humidity-to-location map:"
};

int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;

	std::ifstream		file(av[1]);
	std::string			line;

	if (!file.is_open())
		return 1;

	std::vector<uint32_t>	seeds;
	std::vector<Range>		seed_range;
	ConTable				table;
	size_t					i(0);

	if (!std::getline(file, line))			return 1;
	if (!get_seeds(line, seeds))			return 1;
	if (!get_seed_range(line, seed_range))	return 1;

	while (std::getline(file, line)) {
		if (line.empty())				continue;
		if (mappings[i].empty())		break;
		if (!line.compare(mappings[i])) {
			std::vector<std::string>	lines;
			while (std::getline(file, line) && !line.empty())
				lines.push_back(line);
			if (get_con_table(lines, table)) {
				convert_values(seeds, table);
				convert_ranges(seed_range, table);
				table.clear();
			}
			++i;
		}
	}
	file.close();
	std::cout	<< "Result 1: " \
				<< *(std::min_element(seeds.begin(), seeds.end())) \
				<< std::endl;
	std::cout	<< "Result 2: " \
				<< find_min(seed_range) \
				<< std::endl;
	return 0;
}
