/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 06:02:08 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/24 06:02:08 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <fstream>
# include <iostream>
# include <sstream>
# include <string>
# include <vector>

typedef std::vector<std::string>		StringVector;

unsigned int	count_intersections(StringVector const &input);

#endif // HEAD_HPP
