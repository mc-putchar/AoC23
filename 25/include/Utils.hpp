/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 07:27:06 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/04 07:27:06 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <string>
# include <vector>

size_t						gcd(size_t a, size_t b);
size_t						lcm(size_t a, size_t b);
std::vector<std::string>	ft_splitstr(std::string const &string,
							std::string const &delims);

#endif	// UTILS_H
