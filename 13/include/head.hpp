/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 06:07:19 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/13 06:07:19 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <algorithm>
# include <cstdlib>
# include <fstream>
# include <iostream>
# include <numeric>
# include <sstream>
# include <string>
# include <vector>

typedef std::vector<std::string> StringVector;

int				get_reflection(StringVector const &lines);
StringVector	rotate(StringVector const &matrix);
int				get_better_reflection(StringVector const &lines, bool rotated);
bool			unsmudge(std::string const &lin1, std::string const &lin2, \
				bool &flip);

#endif // HEAD_HPP
