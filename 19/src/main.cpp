/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 06:51:39 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/19 06:51:39 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Workflow.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)				return 1;
	std::ifstream				file(av[1]);
	if (!file.is_open())		return 1;
	std::string					line;
	StringVector				workflows;
	StringVector				parts;

	while (std::getline(file, line) && !line.empty()) {
		workflows.push_back(line);
	}
	while (std::getline(file, line) && !line.empty()) {
		parts.push_back(line);
	}
	file.close();
	std::cout	<< "Result 1: "
				<< organize(parts, workflows)
				<< std::endl;
	std::cout	<< "Result 2: "
				<< summarize(get_workflows(workflows))
				<< std::endl;
	return 0;
}
