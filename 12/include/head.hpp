/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:47:06 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/12 20:47:06 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <algorithm>
# include <fstream>
# include <future>
# include <iostream>
# include <numeric>
# include <sstream>
# include <string>
# include <thread>
# include <vector>

typedef std::pair<std::string, std::vector<int> > Row;
typedef std::vector<std::future<int> > FutureVector;

std::string			analyze(std::string const &line, std::vector<int> &groups);
int					backtrack(std::string const &row,
					std::vector<int> const &groups,
					size_t const &acc);
std::string			unfold(std::string const &row,
					std::vector<int> const &groups,
					std::vector<int> &unfolded_groups);
unsigned long int	accumulate_futures(std::vector<Row> &rows);

#endif // HEAD_HPP
