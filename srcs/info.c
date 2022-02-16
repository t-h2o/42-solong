/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tgrivel@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:18:01 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/16 16:58:56 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"sl.h"

static void
	count_item(t_info *info, char c, int x, int y)
{
	if (c == 'P')
	{
		info->px = x;
		info->py = y;
		info->player += 1;
	}
	if (c == 'C')
		info->coll += 1;
	if (c == 'E')
		info->exit += 1;
}

static void
	get_info(t_info *info, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			count_item(info, map[y][x], x, y);
	}
}

void
	info_map(t_info *info)
{
	info->player = 0;
	info->coll = 0;
	info->exit = 0;
	get_info(info, info->map);
	if (!info->exit)
		it_is_the_end(info, 1, "Error, no exit door");
	if (!info->coll)
		it_is_the_end(info, 1, "Error, no collectible");
	if (info->player != 1)
		it_is_the_end(info, 1, "Error, number of player != 1");
}
/*	Give the position of the player by x and y.
 *	Give the number of collectible in the map
 */
