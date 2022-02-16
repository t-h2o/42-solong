/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:18:19 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/16 16:59:39 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"sl.h"

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void
	all_one(t_info *info, char *str)
{
	while (*str)
	{
		if (*str != '1')
			it_is_the_end(info, 1, "Error, missing a wall (top/bottom)");
		str++;
	}
}

static void
	map_error_wall(t_info *info, char **map)
{
	int	y;

	y = -1;
	all_one(info, map[0]);
	while (map[++y])
	{
		if (ft_strlen(map[y]) != info->lenght)
			it_is_the_end(info, 1, "Error, not same lenght");
		if (map[y][0] != '1' || map[y][info->lenght - 1] != '1')
			it_is_the_end(info, 1, "Error, missing wall (left/right)");
	}
	all_one(info, map[y - 1]);
}

static void
	map_create(t_info *info, char *file)
{
	int		fd;
	int		i;

	info->map = (char **)malloc(sizeof(char *) * 16);
	if (!info->map)
		it_is_the_end(info, 0, "Error, malloc map");
	fd = open(file, O_RDONLY);
	info->width = 0;
	i = 0;
	while (i < 16)
	{
		info->map[i] = get_next_line(fd);
		info->width = i + 1;
		if (!info->map[i])
			break ;
		i++;
	}
	close(fd);
	printf("La hauteur vaut %d\n", info->width);
	if (info->width < 4)
		it_is_the_end(info, 1, "Error, too few line");
	if (info->width >= 16)
		it_is_the_end(info, 1, "Error, too much line");
}
/*	malloc the tab of 16 of line
 *	and set every line in the map
 */

void
	sl_map(t_info *info, char *file)
{
	map_create(info, file);
	info->lenght = ft_strlen(info->map[0]);
	printf("\n1st line is %d lenght\n\n", info->lenght);
	map_error_wall(info, info->map);
}
/*	set the map,
 *	or exit if error
 */
