/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:16:05 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/04 10:16:05 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<std::string>::iterator vectit;

std::string const	nums("0123456789");

static int get_part_num(std::string const &str)
{
	std::istringstream	ss;
	int					n;

	ss.str(str);
	ss >> n;
	if (ss.fail())
		return 0;
	return n;
}

static bool is_attached(std::string const &line, \
						std::string::size_type start, \
						std::string::size_type end)
{
	std::string::size_type	found;

	if (start)	--start;
	found = line.find_first_not_of(nums + ".", start);
	if (end == std::string::npos)
		return (found != std::string::npos);
	return (found != std::string::npos && found < end + 1);
}

static int sum_part_nums(std::vector<std::string> const &schem)
{
	int		res(0);
	size_t	row(0);

	while (row < schem.size()) {
		std::string::size_type	start;
		std::string::size_type	end(0);

		while ((start = schem[row].find_first_of(nums, end)) \
		!= std::string::npos) {
			end = schem[row].find_first_not_of(nums, start);
			if (start && schem[row][start - 1] != '.') {
				res += get_part_num(&schem[row][start]);
				continue;
			}
			if (end != std::string::npos && schem[row][end] != '.') {
				res += get_part_num(&schem[row][start]);
				continue;
			}
			if (row && is_attached(schem[row - 1], start, end)) {
				res += get_part_num(&schem[row][start]);
				continue;
			}
			if (row + 1 < schem.size() && is_attached(schem[row + 1], start, end)) {
				res += get_part_num(&schem[row][start]);
				continue;
			}
		}
		++row;
	}
	return res;
}

static inline bool is_digit(int c) { return (c >= '0' && c <= '9'); }

static int extract_part_num(std::string const &line, std::string::size_type i)
{
	while (i && is_digit(line[i - 1])) { --i; }
	return (get_part_num(&line[i]));
}

static int sum_gear_ratios(std::vector<std::string> const &schem)
{
	int		res(0);
	size_t	row(0);

	while (row < schem.size()) {
		std::string::size_type	next(0);

		while ((next = schem[row].find("*", next)) != std::string::npos) {
			std::vector<int>	parts;

			if (next && is_digit(schem[row][next - 1]))
				parts.push_back(extract_part_num(schem[row], next - 1));
			if (is_digit(schem[row][next + 1]))
				parts.push_back(get_part_num(&schem[row][next + 1]));
			if (row) {
				if (is_digit(schem[row - 1][next]))
					parts.push_back(extract_part_num(schem[row - 1], next));
				else {
					if (next && is_digit(schem[row - 1][next - 1]))
						parts.push_back(extract_part_num(schem[row - 1], next - 1));
					if (is_digit(schem[row - 1][next + 1]))
						parts.push_back(get_part_num(&schem[row - 1][next + 1]));
				}
			}
			if (row + 1 < schem.size()) {
				if (is_digit(schem[row + 1][next]))
					parts.push_back(extract_part_num(schem[row + 1], next));
				else {
					if (next && is_digit(schem[row + 1][next - 1]))
						parts.push_back(extract_part_num(schem[row + 1], next - 1));
					if (is_digit(schem[row + 1][next + 1]))
						parts.push_back(get_part_num(&schem[row + 1][next + 1]));
				}
			}
			if (parts.size() == 2)
				res += parts[0] * parts[1];
			++next;
		}
		++row;
	}
	return res;
}

int main(int ac, char **av)
{
	if (ac != 2)	return 1;

	std::ifstream				file(av[1]);
	std::string					line;
	std::vector<std::string>	schem;

	if (!file.is_open())	return 1;
	while (std::getline(file, line)) {
		schem.push_back(line);
	}
	file.close();
	std::cout << "Result 1: " << sum_part_nums(schem) << std::endl;
	std::cout << "Result 2: " << sum_gear_ratios(schem) << std::endl;
	return 0;
}
