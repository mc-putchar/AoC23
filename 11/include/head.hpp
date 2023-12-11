/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:14:00 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/11 07:14:00 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <algorithm>
# include <cstdlib>
# include <fstream>
# include <iostream>
# include <map>
# include <string>
# include <vector>

typedef unsigned long int uint64_t;

void		expand(std::vector<std::string> &universe,
					std::vector<size_t> &empty_rows,
					std::vector<size_t> &empty_cols);
uint64_t	measure(std::vector<std::string> const &universe,
					std::vector<size_t> const &empty_rows,
					std::vector<size_t> const &empty_cols,
					int k);

#endif // HEAD_HPP
