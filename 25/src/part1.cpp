/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 06:05:03 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/25 06:05:03 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"
#include "Utils.hpp"

namespace {
	static const int	k_degeneracy = 4;
}

typedef std::vector<std::vector<bool> >	AdjacencyMatrix;
typedef std::vector<std::vector<int> > AdjacencyList;

int	has_component(std::string const &c, StringVector const &comps)
{
	for (size_t i = 0; i < comps.size(); ++i) {
		if (!c.compare(comps[i])) { return i; }
	}
	return -1;
}

static void	add_to_matrix(AdjacencyMatrix &adj_matrix)
{
	adj_matrix.push_back(std::vector<bool>(adj_matrix.size(), false));
	for (AdjacencyMatrix::iterator it = adj_matrix.begin();
	it != adj_matrix.end(); ++it) {
		it->push_back(false);
	}
}

std::stack<size_t>	dfs(AdjacencyMatrix const &cxs,
					std::vector<size_t> const &distances,
					size_t start, size_t end)
{
	size_t				next(start);
	std::stack<size_t>	path;
	std::vector<bool>	visited(cxs.size(), false);
	std::vector<size_t>	neighbors;

	path.push(start);
	visited[start] = true;
	while (next != end) {
		neighbors.clear();
		for (size_t i = 0; i < cxs.size(); ++i) {
			if (cxs[next][i] && !visited[i]) {
				neighbors.push_back(i);
			}
		}
		if (!neighbors.empty()) {
			size_t	closest(0), closest_distance(distances[neighbors[0]]);
			for (size_t i = closest + 1; i < neighbors.size(); ++i) {
				if (distances[neighbors[i]] < closest_distance) {
					closest = i;
					closest_distance = distances[neighbors[i]];
				}
			}
			path.push((next = neighbors[closest]));
			visited[next] = true;
			continue;
		}
		if (path.empty()) { return path; }
		next = path.top(); path.pop();
	}
	return path;
}

std::vector<size_t>	bfs(AdjacencyMatrix const &cxs, size_t start, size_t end)
{
	std::vector<bool>	visited(cxs.size(), false);
	std::vector<size_t>	distances(cxs.size(), cxs.size() + 1);
	size_t				next(start);
	std::queue<size_t>	explore;

	distances[start] = 0;
	distances[end] = 0;
	explore.push(start);
	while (!explore.empty()) {
		next = explore.front(); explore.pop();
		visited[next] = true;
		for (size_t i = 0; i < cxs.size(); ++i) {
			if (cxs[next][i] && !visited[i]) {
				if (distances[i] < distances[next] + 1) {
					distances[i] = distances[next] + 1;
				}
				explore.push((next = i));
			}
		}
	}
	return distances;
}

/* snip */
int	min_cut(AdjacencyMatrix cxs, size_t src, size_t sink)
{
	int					capacity(std::min(
						std::count(cxs[src].begin(), cxs[src].end(), true),
						std::count(cxs[sink].begin(), cxs[sink].end(), true)));
	int					flow(0);
	std::vector<size_t>	distances(bfs(cxs, src, sink));
	std::stack<size_t>	path(dfs(cxs, distances, src, sink));
	size_t				first;

	while (!path.empty() && ++flow <= capacity) {
		while (!path.empty()) {
			first = path.top(); path.pop();
			std::cout << first << " > ";
			if (path.empty())	break;
			cxs[first][path.top()] = false;
			cxs[path.top()][first] = false;
		}
		std::cout << std::endl;
		path = dfs(cxs, bfs(cxs, src, sink), src, sink);
	}
	return flow;
}

void	find_cut(AdjacencyMatrix &cxs)
{
	int	n;

	for (size_t i = 0; i < cxs.size() - 1; ++i) {
		for (size_t j = i + 1; j < cxs.size(); ++j) {
			if (!cxs[i][j]) { continue; }
			cxs[i][j] = false;
			cxs[j][i] = false;
			// std::cout << min_cut(cxs, i, j) << std::endl;
			n = min_cut(cxs, i, j);
			if (n && n < k_degeneracy - 1) {
				std::cout << "Cut at: " << i << " and " << j 
				<< " \tFlow: " << n << std::endl;
			}
			cxs[i][j] = true;
			cxs[j][i] = true;
		}
	}
}

std::vector<size_t>	get_indices(std::vector<int> const &tracker)
{
	std::vector<size_t>	indices;

	for (size_t i = 0; i < tracker.size(); ++i) {
		if (tracker[i]) {
			indices.push_back(i);
		}
	}
	return indices;
}

bool	contract(AdjacencyList &edges, std::vector<int> &tracker)
{
	std::vector<size_t>	selector(get_indices(tracker));
	int					n(selector[std::rand() % selector.size()]);
	int					sel;
	std::vector<int>	common;

	// while (edges[n].size() < 2) {
	// 	n = selector[std::rand() % selector.size()];
	// }
	sel = edges[n][std::rand() % edges[n].size()];
	tracker[n] += tracker[sel];
	tracker[sel] -= tracker[sel];
	for (size_t i = 0; i < edges[n].size(); ++i) {
		for (size_t j = 0; j < edges[sel].size(); ++j) {
			if (edges[n][i] == edges[sel][j]) {
				common.push_back(edges[n][i]);
				break;
			}
		}
	}
	for (size_t i = 0; i < edges[sel].size(); ++i) {
		// if (std::find(common.begin(), common.end(), edges[sel][i])
		// != common.end()) {
		// 	continue;
		// }
		for (std::vector<int>::iterator it = edges[edges[sel][i]].begin();
		it != edges[edges[sel][i]].end(); ++it) {
			if (*it == sel) {
				if (std::find(common.begin(), common.end(), edges[sel][i])
				!= common.end()) {
					edges[edges[sel][i]].erase(it);
				} else {
					edges[n].push_back(edges[sel][i]);
					*it = n;
				}
				break;
			}
		}
	}
	return (selector.size() > 3);
}

size_t	karger(AdjacencyList edges)
{
	std::vector<int>	tracker(edges.size(), 1);
	size_t				remaining(0);

	while (contract(edges, tracker)) {;}
	for (size_t i = 0; i < tracker.size(); ++i) {
		if (tracker[i]) {
			// std::cout << tracker[i] << " x ";
			remaining = edges[i].size();
			std::cout << i << ": " << tracker[i] << " >> ";
			for (std::vector<int>::const_iterator it = edges[i].begin();
			it != edges[i].end(); ++it) {
				std::cout << *it << " ";
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	return remaining;
}

AdjacencyList	build_adj_list(AdjacencyMatrix const &matrix)
{
	AdjacencyList	adj_list(matrix.size());

	for (size_t j = 0; j < matrix.size(); ++j) {
		for (size_t i = 0; i < matrix[j].size(); ++i) {
			if (matrix[j][i]) {
				adj_list[j].push_back(i);
			}
		}
	}
	return adj_list;
}

void	parse_input(const StringVector &input)
{
	std::string::size_type	pos;
	std::string				component;
	StringVector			collection;
	AdjacencyMatrix			connections;

	for (StringVector::const_iterator line = input.begin();
	line != input.end(); ++line) {
		int		lhs(-1), rhs(-1);
		pos = line->find(':');
		if (pos == std::string::npos) { continue; }
		component = line->substr(0, pos);
		if ((lhs = has_component(component, collection)) < 0) {
			collection.push_back(component);
			add_to_matrix(connections);
			lhs = collection.size() - 1;
		}
		StringVector	edges(ft_splitstr(line->substr(pos + 2), " "));
		for (StringVector::const_iterator it = edges.begin();
		it != edges.end(); ++it) {
			if ((rhs = has_component(*it, collection)) < 0) {
				collection.push_back(*it);
				add_to_matrix(connections);
				rhs = collection.size() - 1;
			}
			connections[lhs][rhs] = true;
			connections[rhs][lhs] = true;
		}
	}
	// for (AdjacencyMatrix::const_iterator it = connections.begin();
	// it != connections.end(); ++it) {
	// 	std::cout << collection[it - connections.begin()] << ": ";
	// 	for (std::vector<bool>::const_iterator con = it->begin();
	// 	con != it->end(); ++con) {
	// 		// std::cout << *con << " ";
	// 	}
	// 	// std::cout << "edges: " << std::count(it->begin(), it->end(), true) << std::endl;
	// }
	// std::cout << std::endl;
	// find_cut(connections);
	AdjacencyList		adj_list(build_adj_list(connections));
	size_t				cuts(k_degeneracy);
	while (cuts > k_degeneracy - 1) {
		cuts = karger(adj_list);
	}
	std::cout << cuts << std::endl;
}
