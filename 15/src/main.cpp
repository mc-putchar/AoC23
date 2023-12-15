/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 06:10:22 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/15 06:10:22 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)				return 1;
	std::ifstream				file(av[1]);
	if (!file.is_open())		return 1;
	std::string					line;
	StringVector				lines;
	unsigned int				res(0);

	while (std::getline(file, line, ',')) {
		lines.push_back(line);
		res += calculate_hash(line);
	}
	file.close();
	std::cout	<< "Result 1: "
				<< res
				<< std::endl;
	std::cout	<< "Result 2: "
				<< run_ops(lines)
				<< std::endl;
	return 0;
}

int	calculate_hash(std::string const &str)
{
	int	hash(0);

	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
		if (*it == '\n')	break;
		hash += static_cast<unsigned char>(*it);
		hash = (hash + (hash << 4)) & 0xFF;
	}
	return (hash & 0xFF);
}

struct has_label
{
	has_label(std::string const &label) : label_(label)
	{}

	bool operator()(std::pair<std::string, int> const &lens) const
	{
		return (label_ == lens.first);
	}

	std::string const	label_;
};

int	run_ops(StringVector const &lines)
{
	LensBox	boxes[256];

	for (StringVector::const_iterator it = lines.begin();
	it != lines.end(); ++it) {
		int						box_number;
		int						lens;
		std::string				label;
		std::string::size_type	pos(it->find('-'));
		if (pos == std::string::npos) {
			pos = it->find('=');
			label = it->substr(0, pos);
			box_number = calculate_hash(label);
			std::istringstream(it->substr(pos + 1)) >> lens;
			LensBox::iterator box = std::find_if(boxes[box_number].begin(),
											boxes[box_number].end(),
											has_label(label));
			if (box == boxes[box_number].end()) {
				boxes[box_number].insert(box, std::make_pair(label, lens));
			} else {
				box->second = lens;
			}
		} else {
			label = it->substr(0, pos);
			box_number = calculate_hash(label);
			boxes[box_number].remove_if(has_label(label));
		}
	}
	int	sum(0);
	for (int i = 0; i < 256; ++i) {
		if (boxes[i].empty())	continue;
		int	n(0);
		for (LensBox::const_iterator lens = boxes[i].begin();
		lens != boxes[i].end(); ++lens) {
			sum += (i + 1) * (++n) * lens->second;
		}
	}
	return sum;
}
