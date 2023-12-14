/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:28:54 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/14 11:28:54 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

// # include <algorithm>
# include <fstream>
# include <iostream>
# include <string>
# include <vector>

typedef std::vector<std::string> StringVector;

void	tilt_north(StringVector &platform);
int		calculate_load(StringVector &platform);
int		spin_cycle(StringVector &platform, int n);

#endif // HEAD_HPP
