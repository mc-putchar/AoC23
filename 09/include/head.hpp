/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 05:55:53 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/09 05:55:53 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <algorithm>
# include <fstream>
# include <iostream>
# include <numeric>
# include <sstream>
# include <string>
# include <vector>

std::vector<int>	fill_values(std::string const &line);
int					extrapolate(std::vector<int> const &history);
int					uno_reverse(std::vector<int> const &history);

#endif // HEAD_HPP
