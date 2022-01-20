/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:18:19 by tgrivel           #+#    #+#             */
/*   Updated: 2022/01/20 18:19:06 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"sl.h"

static int
	all_one(char *line, int *len)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '1')
		{
			printf("There is a hole up or down side\n");
			return (1);
		}
	}
	if (*len && i != *len)
	{
		printf("last line isn't same size\n");
		return (1);
	}
	*len = i;
	return (0);
}

static int
	map_error(char **map, int *lenght)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	if (all_one(map[0], &len))
		return (1);
	j = 0;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if ((i == 0 || i == len - 1) && map[j][i] != '1')
			{
				printf("There is a hole right or left\n");
				return (1);
			}
		}
		if (len != i)
		{
			printf("There is asometrie\n");
			return (1);
		}
	}
	if (all_one(map[j - 1], &len))
		return (1);
	*lenght = len;
	return (0);
}

static int
	width_counter(char *s)
{
	char	*l;
	int		fd;
	int		n;

	n = 0;
	fd = open(s, O_RDONLY);
	if (read(fd, 0, 0) != 0)
		exit(0);
	n = 0;
	l = (char *) 1;
	while (l)
	{
		l = get_next_line(fd);
		if (!n && !l)
			exit(0);
		free(l);
		n++;
	}
	if (n < 4)
		exit(0);
	close(fd);
	return (n);
}

static char
	**map_create(char *s, int *width)
{
	int		fd;
	int		i;
	char	**r;

	*width = width_counter(s);
	r = (char **)malloc(sizeof(char *) * *width);
	if (!r)
		return (0);
	r[*width] = 0;
	fd = open(s, O_RDONLY);
	i = 0;
	while (i < *width)
		r[i++] = get_next_line(fd);
	close(fd);
	return (r);
}

char
	**sl_map(char *s, int *lenght, int *width)
{
	char	**r;

	*lenght = 0;
	*width = 0;
	r = map_create(s, width);
	if (!r)
	{
		printf("Error, malloc\n");
		exit(0);
	}
	if (map_error(r, lenght))
		exit(0);
	return (r);
}
