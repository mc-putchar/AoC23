/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 11:51:58 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/23 11:51:58 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Graph.hpp"

static std::vector<Node>	neighbors(StringVector const &map, Node const &n)
{
	std::vector<Node>	neighbors;

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

static void	reload(std::vector<Node> const &vec, std::stack<Node> &stack)
{
	for (std::vector<Node>::const_reverse_iterator it = vec.rbegin();
	it != vec.rend(); ++it) {
		stack.push(*it);
	}
}

static Graph	construct_graph(StringVector const &map)
{
	Graph				graph;
	Node				next(map[0].find('.'), 0);
	std::stack<Node>	explore;
	std::vector<Node>	edges;
	size_t const		len(map[0].length());
	std::vector<bool>	visited(map.size() * len, false);

	reload(neighbors(map, next), explore);
	while (!explore.empty()) {
		next = explore.top(); explore.pop();
		visited[next.hash(len)] = true;
		edges = neighbors(map, next);
		if (edges.size() == 1 || edges.size() > 2) { graph.add_node(next); }
		for (std::vector<Node>::const_iterator edge = edges.begin();
		edge != edges.end(); ++edge) {
			if (!visited[edge->hash(len)]) { explore.push(*edge); }
		}
	}
	for (std::vector<Node>::const_iterator node = graph.nodes().begin();
	node != graph.nodes().end(); ++node) {
		std::vector<Node>	path;
		reload(neighbors(map, *node), explore);
		visited[node->hash(len)] = false;
		while (!explore.empty()) {
			next = explore.top(); explore.pop();
			visited[next.hash(len)] = false;
			path.push_back(next);
			edges = neighbors(map, next);
			if (edges.size() != 2) {
				graph.add_edge(graph.has_node(*node),
					graph.has_node(next), path.size());
				for (size_t i = 0; i < path.size(); ++i) {
					visited[path[i].hash(len)] = true;
				}
				path.clear();
				continue;
			}
			for (std::vector<Node>::const_iterator edge = edges.begin();
			edge != edges.end(); ++edge) {
				if (visited[edge->hash(len)]) { explore.push(*edge); }
			}
		}
		visited[node->hash(len)] = true;
	}
	return graph;
}

struct distance
{
	int	g;
	int h;
	int f() const { return g + h; }
	distance() : g(0), h(0) {}
	distance(int a, int b) : g(a), h(b) {}
	distance(distance const &d) : g(d.g), h(d.h) {}
	distance &operator=(distance const &rhs) {
		if (this != &rhs) {
			this->g = rhs.g;
			this->h = rhs.h;
		}
		return *this;
	}
};

struct Connection
{
	int			node;
	int			parent;
	distance	dist;
	Connection() {}
	Connection(int to, int from, distance d) : node(to), parent(from), dist(d){}
};

struct shorter_dist
{
	bool operator()(Connection const &lhs, Connection const &rhs) {
		return (lhs.dist.f() == rhs.dist.f() ? lhs.dist.h < rhs.dist.h
											: lhs.dist.f() < rhs.dist.f());
	}
};

struct longer_dist
{
	bool operator()(Connection const &lhs, Connection const &rhs) {
		return (lhs.dist.f() == rhs.dist.f() ? lhs.dist.h > rhs.dist.h
											: lhs.dist.f() > rhs.dist.f());
	}
};

static int	estimate(Graph const &g, int start, int end)
{
	return (std::abs(g.nodes()[end].x() - g.nodes()[start].x())
		+ std::abs(g.nodes()[end].y() - g.nodes()[start].y()));
}

int	a_star_search(Graph const &graph, int end, std::vector<bool> visited)
{
	std::priority_queue<Connection,
		std::vector<Connection>, longer_dist>	unvisited;
	int											next(graph.nodes().size() - 1);
	distance									dist;
	Connection									con;
	std::vector<Connection>						path;

	unvisited.push(Connection(next, -1, dist));
	while (!unvisited.empty()) {
		con = unvisited.top(); unvisited.pop();
		path.push_back(con);
		next = con.node;
		dist = con.dist;
		if (next == end) {
			break;
		}
		visited[next] = true;
		for (std::vector<std::pair<int, int> >::const_iterator
		it = graph.edges()[next].begin();
		it != graph.edges()[next].end(); ++it) {
			if (!visited[it->first]) {
				distance	d(dist.g + it->second,
							estimate(graph, it->first, end));
				unvisited.push(Connection(it->first, next, d));
			}
		}
	}
	return dist.g;
}

void	print_path(std::vector<Connection> const &path, int end)
{
	std::cout << "Final path: ";
	for (std::vector<Connection>::const_reverse_iterator it = path.rbegin();
	it != path.rend(); ++it) {
		if (it->node != end) { continue; }
		std::cout << it->node << " ";
		end = it->parent;
	}
	std::cout << std::endl;
}

int	dfs(Graph const &graph, int node, std::vector<bool> visited)
{
	int dist(0), max_dist(0), step(0);

	if (node && graph.edges()[node].size() == 1U) {
		return 1;
	}
	visited[node] = true;
	for (std::vector<std::pair<int, int> >::const_iterator
	it = graph.edges()[node].begin();
	it != graph.edges()[node].end(); ++it) {
		if (!visited[it->first]
		&& (dist = dfs(graph, it->first, visited)) > max_dist) {
			max_dist = dist;
			step = it->second;
		}
	}
	return max_dist + step;
}

unsigned int	most_scenic_path(StringVector const &map)
{
	Graph				graph(construct_graph(map));
	std::vector<bool>	visited(graph.nodes().size(), false);

	return (dfs(graph, 0, visited) - 1);

	// int	i(0);
	// for (std::vector<Node>::const_iterator it = graph.nodes().begin();
	// it != graph.nodes().end(); ++it) {
	// 	std::cout << i << ": [" << *it << "] >> ";
	// 	for (std::vector<std::pair<int, int> >::const_iterator edge = graph.edges()[i].begin();
	// 	edge != graph.edges()[i].end(); ++edge) {
	// 		std::cout << "[" << edge->first << ":" << edge->second << "] ";
	// 	}
	// 	++i;
	// 	std::cout << std::endl;
	// }
}
