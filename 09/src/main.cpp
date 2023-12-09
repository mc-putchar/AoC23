/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 05:56:03 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/09 07:39:42 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Utils.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)	return 1;

	std::ifstream	file(av[1]);
	std::string		line;
	int				res(0), res2(0);

	if (!file.is_open())	return 1;

	while (std::getline(file, line)) {
		if (line.empty())		continue;
		std::vector<int>		history(fill_values(line));
		if (history.empty())	continue;

		res += extrapolate(history);
		res2 += uno_reverse(history);
	}
	file.close();

	std::cout	<< "Result 1: " << res << std::endl;
	std::cout	<< "Result 2: " << res2 << std::endl;
	return 0;
}

std::vector<int>	fill_values(std::string const &line)
{
	std::vector<std::string>	tmp(ft_splitstr(line, " "));
	std::vector<int>			hist;

	for(std::vector<std::string>::const_iterator it = tmp.begin(); \
	it != tmp.end(); std::advance(it, 1)) {
		int	val(0);
		std::istringstream(*it) >> val;
		hist.push_back(val);
	}
	return hist;
}

static bool	neqz(int n)		{ return n; }

static int	derivate(std::vector<int> const &vals)
{
	if (vals.size() < 2)	return 0;
	std::vector<int>		deriv;

	std::adjacent_difference(vals.begin(), vals.end(), \
		std::back_inserter(deriv));
	deriv.erase(deriv.begin());
	if (std::find_if(deriv.begin(), deriv.end(), neqz) != deriv.end())
		return (deriv.back() + derivate(deriv));
	return 0;
}

int	extrapolate(std::vector<int> const &history)
{
	return history.back() + derivate(history);
}

static int	back_derivate(std::vector<int> const &vals)
{
	if (vals.size() < 2)	return 0;
	std::vector<int>		deriv;

	std::adjacent_difference(vals.begin(), vals.end(), \
		std::back_inserter(deriv));
	deriv.erase(deriv.begin());
	if (std::find_if(deriv.begin(), deriv.end(), neqz) != deriv.end())
		return (deriv.front() - back_derivate(deriv));
	return 0;
}

int	uno_reverse(std::vector<int> const &history)
{
	return history.front() - back_derivate(history);
}
