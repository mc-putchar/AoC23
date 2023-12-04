/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calibrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 05:45:45 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/04 05:45:45 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE	4096

static char const	*nums[] = 
{
"one",
"two",
"three",
"four",
"five",
"six",
"seven",
"eight",
"nine"
};

static int	ft_is_number(char const *num)
{
	int	i;

	if (*num > '0' && *num <= '9')
		return (*num - '0');
	i = -1;
	while (++i < 9)
		if (!strncmp(num, nums[i], strlen(nums[i])))
			return (i + 1);
	return (0);
}

int	calibrate(char const *data)
{
	int		last;
	int		res;
	int		n;

	res = 0;
	last = -1;
	while (*data)
	{
		n = ft_is_number(data);
		if (n)
		{
			if (last < 0)
				res += n * 10;
			last = n;
		}
		else if (*data == '\n')
		{
			if (last > 0)
				res += last;
			last = -1;
		}
		++data;
	}
	if (last > 0)
		res += last;
	return (res);
}

int	main(int ac, char **av)
{
	int		fd;
	char	buff[BUFFER_SIZE];
	ssize_t	r;
	size_t	done;
	size_t	size;
	char	*data;
	int		res;

	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	size = 0;
	r = read(fd, buff, BUFFER_SIZE);
	while (r > 0)
	{
		size += (size_t)r;
		r = read(fd, buff, BUFFER_SIZE);
	}
	if (close(fd) || r < 0 || !size)
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	data = malloc(size + 1);
	if (!data)
		return (close(fd), printf("ENOMEM\n"), 1);
	data[size] = 0;
	done = 0;
	r = read(fd, data, size);
	while (r > 0 && done < size)
	{
		done += r;
		r = read(fd, data + done, size - done);
	}
	close(fd);
	if (r < 0)
		return (free(data), 1);
	printf("Calibration accumulated: %d\n", calibrate(data));
	return (free(data), 0);
}
