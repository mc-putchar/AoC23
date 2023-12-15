/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 06:10:40 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/15 06:10:40 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <algorithm>
# include <fstream>
# include <iostream>
# include <list>
# include <sstream>
# include <string>
# include <vector>

typedef std::vector<std::string> StringVector;
typedef std::list<std::pair<std::string, int> > LensBox;

int	calculate_hash(std::string const &str);
int	run_ops(StringVector const &lines);

#endif // HEAD_HPP
