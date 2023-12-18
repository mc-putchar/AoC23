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
# include <iostream>
# include <map>
# include <numeric>
# include <sstream>
# include <string>
# include <vector>

typedef std::pair<std::string, std::vector<int> > Row;

bool operator<(Row const &lhs, Row const &rhs)
{
	if (lhs.first < rhs.first)	return true;
	if (lhs.first > rhs.first)	return false;
	return (lhs.second < rhs.second);
}

typedef std::map<Row, unsigned long int, std::less<Row> > Cache;

std::string			analyze(std::string const &line, std::vector<int> &groups);
unsigned long int	backtrack(std::string const &row,
					std::vector<int> const &groups,
					size_t const &acc);
std::string			unfold(std::string const &row,
					std::vector<int> const &groups,
					std::vector<int> &unfolded_groups);

Row					unfold(Row const &row);
unsigned long int	dynamic(Row const &row);

#endif // HEAD_HPP
