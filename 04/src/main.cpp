/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:50:08 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/04 13:50:08 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Utils.hpp"

typedef std::vector<std::string>::iterator vectit;

static int get_card_score(std::string const &line)
{
	std::vector<std::string>	nums = ft_splitstr(line, " ");
	std::vector<int>			winnums;
	int							score(0);
	bool						set(false);

	for (vectit it = nums.begin(); it != nums.end(); ++it) {
		std::istringstream	ss;
		int					n;

		if ((*it)[0] == '|') {
			set = true;
			continue;
		}
		ss.str(*it);
		ss >> n;
		if (!set) {
			winnums.push_back(n);
			continue;
		}
		if (std::find(winnums.begin(), winnums.end(), n) != winnums.end())
			++score;
	}
	return score;
}

static int calc_score(std::vector<int> &scores)
{
	int	acc(0);

	for (std::vector<int>::iterator it = scores.begin(); it != scores.end(); ++it) {
		if (*it)
			acc += 1 << ((*it) - 1);
	}
	return acc;
}

static int calc_scratchees(std::vector<int> &scores, std::vector<int> &mults)
{
	int	acc(0);

	for (size_t i = 0; i < scores.size(); ++i) {
		for (int tmp = 0; tmp < scores[i]; ++tmp)
			mults[i + tmp + 1] += mults[i];
		acc += mults[i];
	}
	return acc;
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;

	std::ifstream		file(av[1]);
	std::string			line;

	if (!file.is_open())
		return 1;

	std::vector<int>	scores;
	std::vector<int>	mults;
	while (std::getline(file, line)) {
		std::vector<std::string> card = ft_splitstr(line, ":");
		if (card.size() != 2)	continue;
		scores.push_back(get_card_score(card[1]));
		mults.push_back(1);
	}
	file.close();
	std::cout << "Result 1: " << calc_score(scores) << std::endl;
	std::cout << "Result 2: " << calc_scratchees(scores, mults) << std::endl;
	return 0;
}
