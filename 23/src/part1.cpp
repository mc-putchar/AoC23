/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 06:03:38 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/23 06:03:38 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Graph.hpp"

typedef std::vector<std::vector<bool> > BoolMatrix;
typedef std::map<int, std::vector<Node> > AdjacencyList;

static std::vector<Node>	neighbors(StringVector const &map, Node const &n)
{
	std::vector<Node>	neighbors;
	switch (map[n.y()][n.x()]) {
		case '>':
			neighbors.push_back(Node(n.x() + 1, n.y()));
			return neighbors;
		case 'v':
			neighbors.push_back(Node(n.x(), n.y() + 1));
			return neighbors;
		case '<':
			neighbors.push_back(Node(n.x() - 1, n.y()));
			return neighbors;
		case '^':
			neighbors.push_back(Node(n.x(), n.y() - 1));
			return neighbors;
		default:	break;
	}
	if (n.x() && map[n.y()][n.x() - 1] != '#' ) {
		neighbors.push_back(Node(n.x() - 1, n.y()));
	}
	if (static_cast<size_t>(n.x() + 1) < map[n.y()].length()
	&& map[n.y()][n.x() + 1] != '#' ) {
		neighbors.push_back(Node(n.x() + 1, n.y()));
	}
	if (n.y() && map[n.y() - 1][n.x()] != '#' ) {
		neighbors.push_back(Node(n.x(), n.y() - 1));
	}
	if (static_cast<size_t>(n.y() + 1) < map.size()
	&& map[n.y() + 1][n.x()] != '#' ) {
		neighbors.push_back(Node(n.x(), n.y() + 1));
	}
	return neighbors;
}

static AdjacencyList	construct_adj_list(StringVector const &map)
{
	size_t const		len(map[0].length());
	BoolMatrix			visited(map.size(),
						std::vector<bool>(map[0].length(), false));
	Node				n(map[0].find('.'), 0);
	AdjacencyList		adjacency_list;
	std::queue<Node>	exploration_q;
	std::vector<Node>	edges;

	exploration_q.push(n);
	while (!exploration_q.empty()) {
		n = exploration_q.front();
		exploration_q.pop();
		visited[n.y()][n.x()] = true;
		edges = neighbors(map, n);
		adjacency_list.insert(std::make_pair(n.hash(len), edges));
		for (std::vector<Node>::const_iterator it = edges.begin();
		it != edges.end(); ++it) {
			if (!visited[it->y()][it->x()])	{ exploration_q.push(*it); }
		}
	}
	return adjacency_list;
}

static void	unwind(std::stack<Node> &path, Node node, BoolMatrix &visited)
{
	Node	n;
	while (!path.empty()) {
		n = path.top();
		if (n == node) { return; }
		path.pop();
		visited[n.y()][n.x()] = false;
	}
}

void print(std::vector<std::stack<Node> > paths)
{
	Node	n;
	for (std::vector<std::stack<Node> >::iterator path = paths.begin();
	path != paths.end(); ++path) {
		std::cout << "steps: " << path->size() << ": ";
		while (!path->empty()) {
			n = path->top(); path->pop();
			std::cout << n << " < ";
		}
		std::cout << std::endl;
	}
}

std::vector<size_t>	dfs(StringVector const &map, AdjacencyList const &adj_list)
{
	size_t const					len(map[0].length());
	Node							next(map[0].find('.'), 0);
	std::stack<Node>				stack;
	std::vector<Node>				edges;
	BoolMatrix						visited(map.size(),
									std::vector<bool>(map[0].length(), false));
	std::stack<Node>				path, branch;
	std::vector<std::stack<Node> >	paths;
	std::vector<size_t>				path_lens;

	stack.push(next);
	while (!stack.empty()) {
		next = stack.top(); stack.pop();
		path.push(next);
		visited[next.y()][next.x()] = true;
		edges = adj_list.find(next.hash(len))->second;
		int					outs(0);
		std::vector<Node>	tmp;
		for (std::vector<Node>::const_iterator it = edges.begin();
		it != edges.end(); ++it) {
			if (visited[it->y()][it->x()]) { continue; }
			tmp = adj_list.find(it->x() + it->y() * len)->second;
			if (tmp.size() == 1 && tmp[0] == next) { continue; }
			stack.push(*it);
			++outs;
		}
		if (!outs) {
			paths.push_back(path);
			path_lens.push_back(path.size());
			if (!branch.empty()) {
				unwind(path, branch.top(), visited);
				branch.pop();
			}
			continue;
		}
		if (outs > 1) {
			// std::cout << "Branch at: " << next.x << "," << next.y
			// << "\n\tPaths: " << edges.size() << std::endl;
			branch.push(next);
		}
	}
	// print(paths);
	return path_lens;
}

void	print(AdjacencyList const &a_list)
{
	for (AdjacencyList::const_iterator it = a_list.begin();
	it != a_list.end(); ++it) {
		std::cout << it->first << ": ";
		for (std::vector<Node>::const_iterator n = it->second.begin();
		n != it->second.end(); ++n) {
			std::cout << *n << " ";
		}
		std::cout << std::endl;
	}
}

unsigned int	longest_path(StringVector const &map)
{
	AdjacencyList		adj_list(construct_adj_list(map));
	std::vector<size_t>	paths(dfs(map, adj_list));

	std::sort(paths.begin(), paths.end());
	return paths.back();
}
