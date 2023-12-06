/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 05:53:42 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/06 05:53:42 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Utils.hpp"

static void	get_values(std::string const &line, std::vector<uint32_t> &vec)
{
	std::vector<std::string>	spl(ft_splitstr(line, " "));
	uint32_t					n;

	for (VSIter it = spl.begin(); it != spl.end();) {
		std::istringstream(*it) >> n;
		vec.push_back(n);
		std::advance(it, 1);
	}
}

static uint32_t	get_way_count(uint32_t time, uint32_t dist)
{
	uint32_t	first, second, count;

	count = 1U;
	first = time >> 1;
	second = first;
	if (time & 1) {
		++count;
		++second;
	}
	if (first * second < dist)						return 0;
	while ((dist < --first * ++second) && first)	count += 2;
	return count;
}

static uint32_t	get_result1(std::vector<uint32_t> const &times, \
							std::vector<uint32_t> const &distances)
{
	uint32_t	res(1);
	for (std::vector<uint32_t>::size_type i = 0; i < times.size(); ++i) {
		res *= get_way_count(times[i], distances[i]);
	}
	return res;
}

static uint32_t	get_result2(uint64_t time, uint64_t dist)
{
	uint32_t	count(1U);
	uint64_t	first(time >> 1);
	uint64_t	second(time >> 1);

	if (time & 1) {
		++count;
		++second;
	}
	if (second <= dist / first)			return 0;
	while (++second > dist / --first)	count += 2;
	return count;
}

int	main(int ac, char **av)
{
	if (ac != 2)	return 1;

	std::ifstream			file(av[1]);
	std::string				line;
	std::string::size_type	pos;

	if (!file.is_open())	return 1;

	std::vector<uint32_t>	times;
	std::vector<uint32_t>	distances;
	uint64_t				time2(0), dist2(0);

	if (std::getline(file, line) \
	&& (pos = line.find(":")) != std::string::npos) {
		std::string	tmp = line.substr(pos + 1);
		get_values(tmp, times);
		tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
		std::istringstream(tmp) >> time2;
	}
	if (std::getline(file, line) \
	&& (pos = line.find(":")) != std::string::npos) {
		std::string	tmp = line.substr(pos + 1);
		get_values(tmp, distances);
		tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
		std::istringstream(tmp) >> dist2;
	}
	file.close();
	if (times.size() != distances.size() || !time2 || !dist2)	return 1;

	std::cout << "Result 1: " << get_result1(times, distances) << std::endl;
	std::cout << "Result 2: " << get_result2(time2, dist2) << std::endl;

	return 0;
}
