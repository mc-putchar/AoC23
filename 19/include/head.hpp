/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 06:12:23 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/19 06:12:23 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <algorithm>
# include <cstdlib>
# include <fstream>
# include <iostream>
# include <map>
# include <sstream>
# include <stack>
# include <string>
# include <vector>

class Workflow;

typedef std::vector<std::string>					StringVector;
typedef std::map<std::string, Workflow>				WorkMap;
typedef std::pair<uint32_t, std::string>			Match;
typedef std::map<std::string, std::vector<Match> >	MatchMap;

WorkMap					get_workflows(StringVector const &w);
unsigned long int		organize(StringVector const &p, StringVector const &w);
unsigned long long int	summarize(WorkMap const &workmap);

#endif // HEAD_HPP
