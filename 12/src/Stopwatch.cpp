/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stopwatch.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:10:56 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/13 07:10:56 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Stopwatch.hpp"

Stopwatch::Stopwatch()
{
	this->start_ = std::chrono::steady_clock::now();
}

Stopwatch::~Stopwatch()
{
	this->stop_ = std::chrono::steady_clock::now();
	std::cout	<< "Time elapsed: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>\
				(this->stop_ - this->start_).count()
				<< " ms" << std::endl;
}
