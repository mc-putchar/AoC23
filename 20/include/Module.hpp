/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Module.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 06:15:22 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/20 06:15:22 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODULE_HPP
# define MODULE_HPP

# include <algorithm>
# include <map>
# include <string>
# include <vector>

typedef std::vector<std::string>		StringVector;
typedef std::pair<std::string, bool>	Pulse;
typedef std::vector<Pulse>				PulseVector;

class Module
{
	public:
	virtual ~Module();
	Module(Module const &rhs);
	Module &operator=(Module const &rhs);

	StringVector const &dest() const;
	bool has_dest(std::string const &mod) const;
	bool test() const;
	bool set();
	bool reset();
	void add_output(std::string const &out);

	virtual PulseVector pulse(Pulse const &p);

	protected:
	Module();

	private:
	bool				state_;
	StringVector		dest_;
};

class Flipflop : public Module
{
	public:
	Flipflop();
	~Flipflop();
	Flipflop(Flipflop const &rhs);
	Flipflop &operator=(Flipflop const &rhs);

	bool flip();

	virtual PulseVector pulse(Pulse const &p);
};

class Conjunction : public Module
{
	public:
	Conjunction();
	~Conjunction();
	Conjunction(Conjunction const &rhs);
	Conjunction &operator=(Conjunction const &rhs);

	std::map<std::string, bool>	const &inputs() const;
	void register_input(std::string const &input);

	virtual PulseVector pulse(Pulse const &p);

	private:
	std::map<std::string, bool>	inputs_;
};

class Broadcaster : public Module
{
	public:
	virtual PulseVector pulse(Pulse const &p);
};

#endif // MODULE_HPP
