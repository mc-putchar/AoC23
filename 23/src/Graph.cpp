/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graph.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:32:43 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/23 11:32:43 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Graph.hpp"

////////////////////////////////////////////////////////////////////////////////
// --- Canonical ---

Node::Node() : x_(0), y_(0) {}

Node::~Node() {}

Node::Node(int x, int y) : x_(x), y_(y) {}

Node::Node(Node const &rhs) : x_(rhs.x()), y_(rhs.y()) {}

Node &Node::operator=(Node const &rhs)
{
	if (this != &rhs) {
		this->x_ = rhs.x();
		this->y_ = rhs.y();
	}
	return *this;
}

Graph::Graph() {}

Graph::~Graph() {}

Graph::Graph(Graph const &rhs) : nodes_(rhs.nodes()), edges_(rhs.edges()) {}

Graph &Graph::operator=(Graph const &rhs)
{
	if (this != &rhs) {
		this->nodes_.clear();
		this->edges_.clear();
		for (std::vector<Node>::const_iterator it = rhs.nodes().begin();
		it != rhs.nodes().end(); ++it) {
			this->add_node(*it);
		}
		for (std::vector<std::pair<int, int> >::const_iterator
		it = rhs.edges().begin();
		it != rhs.edges().end(); ++it) {
			this->add_edge(it->first, it->second);
		}
	}
	return *this;
}


////////////////////////////////////////////////////////////////////////////////
// --- Operators ---

bool Node::operator<(Node const &rhs) const
{
	return (this->y_ < rhs.y() || (this->y_ == rhs.y() && this->x_ < rhs.x()));
}

bool Node::operator==(Node const &rhs) const
{
	return (this->x_ == rhs.x() && this->y_ == rhs.y());
}

bool Node::operator!=(Node const &rhs) const
{
	return (this->x_ != rhs.x() || this->y_ != rhs.y());
}

////////////////////////////////////////////////////////////////////////////////
// --- Getters/Setters ---

int	Node::x() const
{
	return this->x_;
}

int Node::y() const
{
	return this->y_;
}

int	Node::hash(size_t s) const
{
	return (this->y_ * s + this->x_);
}

std::vector<Node> const &Graph::nodes() const
{
	return this->nodes_;
}

std::vector<std::pair<int, int> > const &Graph::edges() const
{
	return this->edges_;
}

void Graph::add_node(Node const &node)
{
	this->nodes_.push_back(node);
}

void Graph::add_edge(int node_idx, int weight)
{
	this->edges_.push_back(std::make_pair(node_idx, weight));
}


////////////////////////////////////////////////////////////////////////////////
// --- Overloads ---

std::ostream &operator<<(std::ostream &oss, Node const &rhs)
{
	oss << rhs.x() << "," << rhs.y();
	return oss;
}

bool operator<(Node const &lhs, Node const &rhs)
{
	return (lhs.y() < rhs.y() || (lhs.y() < rhs.y() && lhs.x() < rhs.x()));
}
