/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graph.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:30:02 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/23 11:30:02 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_HPP
# define GRAPH_HPP

# include <ostream>
# include <vector>

class Node
{
	public:
	Node();
	~Node();
	Node(int x, int y);
	Node(Node const &rhs);
	Node &operator=(Node const &rhs);

	bool operator<(Node const &rhs) const;
	bool operator==(Node const &rhs) const;
	bool operator!=(Node const &rhs) const;

	int	x() const;
	int	y() const;
	int	hash(size_t s) const;

	private:
	int		x_;
	int		y_;
};

bool			operator<(Node const &lhs, Node const &rhs);
std::ostream 	&operator<<(std::ostream &oss, Node const &rhs);

/* WIP */
class Graph
{
	public:
	Graph();
	~Graph();
	Graph(Graph const &rhs);
	Graph &operator=(Graph const &rhs);

	std::vector<Node> const &nodes() const;
	std::vector<std::pair<int, int> > const &edges() const;
	void add_node(Node const &node);
	void add_edge(int node_idx, int weight);

	private:
	std::vector<Node>					nodes_;
	std::vector<std::pair<int, int> >	edges_;
};

#endif // GRAPH_HPP
