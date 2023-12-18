/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 06:16:50 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/18 06:16:50 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)				return 1;
	std::ifstream				file(av[1]);
	if (!file.is_open())		return 1;
	std::string					line;
	StringVector				lines;

	while (std::getline(file, line)) {
		lines.push_back(line);
	}
	file.close();
	std::cout	<< "Result 1: "
				<< get_area(parse_input(lines, false))
				<< std::endl;
	std::cout	<< "Result 2: "
				<< get_area(parse_input(lines, true))
				<< std::endl;
	return 0;
}

static unsigned int	get_color_from_hex(std::string const &str)
{
	unsigned int			val(0);
	std::string::size_type	pos(str.find_first_not_of("(#)"));

	if (pos == std::string::npos)	{ return 0; }
	while (pos < str.length() && str[pos] != ')') {
		unsigned char	n(str[pos++]);
		if (n > '9') {
			n -= n > 'Z' ? 'a' : 'A';
			n += 10;
		} else {
			n -= '0';
		}
		val = (val << 4) | n;
	}
	return val;
}

static Edge	convert_input_line(std::string const &line, bool swap)
{
	unsigned int	dir(0), step(0);
	std::string		color;
	char			tmp;

	std::istringstream(line) >> tmp >> step >> color;
	switch (tmp) {
		case 'U':	dir = 3; break;
		case 'L':	dir = 2; break;
		case 'D':	dir = 1; break;
		case 'R':	dir = 0; break;
		default:	break;
	}
	unsigned int c = get_color_from_hex(color);
	if (swap)
		return Edge(c & 3, (c >> 4), ((step << 4) | dir));
	return Edge(dir, step, c);
}

std::vector<Edge>	parse_input(StringVector const &lines, bool swap)
{
	std::vector<Edge>	edges;

	for (StringVector::const_iterator it = lines.begin();
	it != lines.end(); ++it) {
		edges.push_back(convert_input_line(*it, swap));
	}
	return edges;
}

void	print_map(size_t rows, size_t cols, std::vector<Edge> const &edges)
{
	std::string		row(cols, '.');
	StringVector	map(rows, row);
	Point			p(0,0);
	for (std::vector<Edge>::const_iterator ed = edges.begin();
	ed != edges.end(); ++ed) {
		map[p.y][p.x] = '#';
		for (int i = 0; i < ed->step; ++i) {
			p.x += ((ed->dir+1)&1)*(1-(ed->dir&2));
			p.y += (ed->dir&1)*(1-(ed->dir&2));
			map[p.y][p.x] = '#';
		}
	}
	for (StringVector::const_iterator it = map.begin(); it != map.end(); ++it) {
		std::cout << *it << std::endl;
	}
}

static long int	polygon_area(std::vector<Point> const &chain, long int b)
{
	long int	shoe(0), lace(0);

	for (size_t i = 0; i < chain.size(); ++i) {
		size_t	j((i + 1) % chain.size());
		shoe += static_cast<long int>(chain[i].x) * chain[j].y;
		lace += static_cast<long int>(chain[i].y) * chain[j].x;
	}
	return (std::abs((shoe - lace) >> 1) + (b >> 1) + 1);
}

long int	get_area(std::vector<Edge> const &edges)
{
	long int			trench(0);
	int					sizex(0), sizey(0);
	Point				p(0, 0);
	std::vector<Point>	points;

	for (std::vector<Edge>::const_iterator ed = edges.begin();
	ed != edges.end(); ++ed) {
		points.push_back(p);
		trench += ed->step;
		p.x += (ed->step) * ((ed->dir+1)&1)*(1-(ed->dir&2));
		p.y += (ed->step) * (ed->dir&1)*(1-(ed->dir&2));
		sizex = std::max(sizex, p.x);
		sizey = std::max(sizey, p.y);
	}
	if (p.x || p.y) {
		std::cout << "Polygon not closed\n";
		return 0;
	}
	// print_map(sizey + 1, sizex + 1, edges);
	return (polygon_area(points, trench));
}
