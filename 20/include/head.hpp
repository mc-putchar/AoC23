/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 06:03:27 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/20 06:03:27 by mcutura          ###   ########.fr       */
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
typedef std::map<std::string, Module*>	ModMap;

ModMap			map_modules(StringVector const &data);
void			print_modules(ModMap const &modules);
void			cleanup(ModMap	&modules);
unsigned int	propagation_product(StringVector const &data);
size_t			turn_on_sand_machine(StringVector const &data);
size_t			lcm(size_t a, size_t b);

#endif // HEAD_HPP
