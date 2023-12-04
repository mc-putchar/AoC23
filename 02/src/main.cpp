/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 07:25:01 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/04 07:25:01 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <sstream>

#include "Utils.hpp"

typedef std::vector<std::string>::iterator vectit;

static bool is_possible(std::string const &game, int rgb)
{
	std::vector<std::string> shows = ft_splitstr(game, ";");
	int n(0);

	for (vectit it = shows.begin(); it != shows.end(); ++it) {
		std::vector<std::string> cubes = ft_splitstr(*it, " ,");
		for (vectit cube = cubes.begin(); cube != cubes.end(); ++cube) {
			std::istringstream ss;
			ss.str(*cube);
			ss >> n;
			if (ss.fail())
				return false;
			++cube;
			if (!(*(cube)).compare("red") && ((rgb >> 16) & 0xFF) < n)
				return false;
			if (!(*cube).compare("green") && ((rgb >> 8) & 0xFF) < n)
				return false;
			if (!(*cube).compare("blue") && (rgb & 0xFF) < n)
				return false;
		}
	}
	return true;
}

static int get_game_power(std::string const &game)
{
	std::vector<std::string> shows = ft_splitstr(game, ";");
	int n(0);
	int pow(0);

	for (vectit it = shows.begin(); it != shows.end(); ++it) {
		std::vector<std::string> cubes = ft_splitstr(*it, " ,");
		for (vectit cube = cubes.begin(); cube != cubes.end(); ++cube) {
			std::istringstream ss;
			ss.str(*cube);
			ss >> n;
			if (ss.fail())	continue;
			++cube;
			if (!(*(cube)).compare("red") && ((pow >> 16) & 0xFF) < n)
				pow = (pow & 0x00FFFF) | (n << 16);
			else if (!(*cube).compare("green") && ((pow >> 8) & 0xFF) < n)
				pow = (pow & 0xFF00FF) | (n << 8);
			else if (!(*cube).compare("blue") && (pow & 0xFF) < n)
				pow = (pow & 0xFFFF00) | n;
		}
	}
	return (((pow >> 16) & 0xFF) * ((pow >> 8) & 0xFF) * (pow & 0xFF));
}

static int get_game_number(std::string const &game)
{
	int n(0);
	std::string::size_type start(game.find(" "));
	std::istringstream ss;

	if (start == std::string::npos)
		return 0;
	ss.str(&game[start]);
	ss >> n;
	if (ss.fail())
		return 0;
	return n;
}

int	main(int ac, char **av)
{
	/* 12 red << 13 green << 14 blue */
	int rgb((0 << 24) | (12 << 16) | (13 << 8) | (14 << 0));
	int	res(0);
	int	res2(0);

	if (ac != 2)
		return 1;

	std::ifstream		file(av[1]);
	std::string			line;

	if (!file.is_open())
		return 1;

	while (std::getline(file, line)) {
		std::vector<std::string> game = ft_splitstr(line, ":");
		if (game.size() != 2)	continue;
		if (is_possible(game[1], rgb)) {
			res += get_game_number(game[0]);
		}
		res2 += get_game_power(game[1]);
	}
	file.close();
	std::cout << "Result 1: " << res << std::endl;
	std::cout << "Result 2: " << res2 << std::endl;
	return 0;
}
