/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hand.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:36:06 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/07 12:36:06 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cctype>
#include <set>
#include <string>

class Hand
{
	public:
		Hand(std::string const &hand, int bet);
		Hand(Hand const &cpy);
		~Hand();

		Hand &operator=(Hand const &rhs);
		bool operator<(Hand const &rhs);

		std::string const	&raw() const;
		int					bet() const;
		int					pow() const;

		void				use_jokers();

	private:
		std::string		raw_;
		int				bet_;
		int				pow_;
		std::set<char>	uniq_;
		bool			jokers_;
};
