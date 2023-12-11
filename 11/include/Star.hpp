/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Star.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 07:47:21 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/11 07:47:21 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>

class Star
{
	public:
	Star(int x, int y);
	~Star();
	Star(Star const &rhs);
	Star &operator=(Star const &rhs);

	int x() const;
	int y() const;

	int distance(Star const &rhs) const;

	private:
	int	x_;
	int	y_;
};
