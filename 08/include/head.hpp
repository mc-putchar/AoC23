/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 05:59:13 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/08 05:59:13 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <algorithm>
# include <fstream>
# include <iostream>
# include <list>
# include <map>
# include <numeric>
# include <string>
# include <vector>

typedef unsigned long int uint64_t;
typedef std::map<std::string, std::pair<std::string, std::string> > NavMap;
typedef NavMap::const_iterator MapCIt;

int			follow_steps(std::string const &instr, NavMap const &map);
uint64_t	ghost_steps(std::string const &instr, NavMap const &map);
uint64_t	find_lcm(uint64_t a, uint64_t b);

#endif // HEAD_HPP
