/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 06:03:03 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/23 06:03:03 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <algorithm>
# include <fstream>
# include <iostream>
# include <queue>
# include <map>
# include <sstream>
# include <stack>
# include <string>
# include <vector>

typedef std::vector<std::string>		StringVector;

unsigned int	longest_path(StringVector const &map);
unsigned int	most_scenic_path(StringVector const &map);

#endif // HEAD_HPP
