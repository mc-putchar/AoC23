/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:48:13 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/07 12:48:13 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Hand.hpp"

static int	get_result1(std::vector<Hand> &vec)
{
	int		res(0);
	size_t	i(0);

	std::sort(vec.begin(), vec.end());
	while (i++ < vec.size())
		res += i * vec[i - 1].bet();
	return res;
}

// no lambda in C++98 :(
static void	update(Hand &h) { h.use_jokers(); }

static int	get_result2(std::vector<Hand> &vec)
{
	std::for_each(vec.begin(), vec.end(), update);
	return get_result1(vec);
}

int	main(int ac, char **av)
{
	if (ac != 2)			return 1;

	std::ifstream		file(av[1]);
	std::string			line;
	std::vector<Hand>	hands;

	if (!file.is_open())	return 1;
	while (std::getline(file, line)) {
		std::string::size_type	pos(line.find(" "));
		int						bet(0);

		if (pos == std::string::npos)	continue;
		std::istringstream(&line[pos + 1]) >> bet;
		hands.push_back(Hand(line.substr(0, pos), bet));
	}
	file.close();

	std::cout << "Result 1: " << get_result1(hands) << std::endl;
	std::cout << "Result 2: " << get_result2(hands) << std::endl;
	return 0;
}
