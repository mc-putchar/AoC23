/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 06:41:52 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/22 06:41:52 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <algorithm>
# include <fstream>
# include <iostream>
# include <queue>
# include <sstream>
# include <string>
# include <vector>

class Brick;

typedef std::vector<std::string>		StringVector;

std::vector<Brick>	parse_input(StringVector const &input);
void				settle_down(std::vector<Brick> &slabs);
unsigned int		disintegration_targets(std::vector<Brick> const &slabs);
unsigned long int	chain_reaction(std::vector<Brick> const &slabs);

#endif // HEAD_HPP
