/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stopwatch.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:08:29 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/13 07:08:29 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STOPWATCH_HPP
# define STOPWATCH_HPP

# include <chrono>
# include <iostream>

class Stopwatch
{
	public:
	Stopwatch();
	~Stopwatch();

	private:
	std::chrono::steady_clock::time_point	start_;
	std::chrono::steady_clock::time_point	stop_;

	/* DELETED */
	Stopwatch(Stopwatch const &rhs);
	Stopwatch &operator=(Stopwatch const &rhs);
};

#endif // STOPWATCH_HPP
