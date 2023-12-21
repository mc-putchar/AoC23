/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 06:09:46 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/21 06:09:46 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <algorithm>
# include <cstdlib>
# include <fstream>
# include <iostream>
# include <map>
# include <queue>
# include <sstream>
# include <string>
# include <vector>

class Module;

typedef std::vector<std::string>		StringVector;

StringVector		simulate(StringVector const &map);
unsigned int		count_reachable(StringVector lines, int steps);
unsigned long int	count_parallel(StringVector lines, int steps);

#endif // HEAD_HPP
