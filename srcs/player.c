/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:18:05 by tgrivel           #+#    #+#             */
/*   Updated: 2022/01/22 17:17:30 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"sl.h"

static int
	sl_conv(char c)
{
	if (c == 'E')
		return (4);
	if (c == 'C')
		return (3);
	if (c == 'P')
		return (2);
	return (c - '0');
}
	/*
	0 empt
	1 wall
	2 play
	3 coll
	4 exit
	5 MLX
	6 MLX_WIN
	*/

static void
	it_is_the_end(t_info *param)
{
	char	**map;
	void	**img;

	map = param->map;
	while (*map)
	{	
		printf("free(%p) : %s\n", *map, *map);
		free(*(map++));
	}
	img = param->img;
	mlx_destroy_window(img[5], img[6]);
	printf("free(%p) : img\n", img);
	free(img);
	exit(0);
}

static void
	move_player(int movex, int movey, t_info *param)
{
	printf("coll : %d\n", param->coll);
	if (param->map[param->py + movey][param->px + movex] == '1')
		return ;
	if (param->map[param->py + movey][param->px + movex] == 'E')
	{
		if (!param->coll)
			it_is_the_end(param);
		return ;
	}
	if (param->map[param->py + movey][param->px + movex] == 'C')
		param->coll--;
	param->move++;
	printf("move number : %d\n", param->move);
	param->map[param->py][param->px] = '0';
	param->px += movex;
	param->py += movey;
	param->map[param->py][param->px] = 'P';
	sl_displaymap(param->map, param->img, param->move);
}

char
	*ft_itoa(int n)
{
	char	*r;
	int		len;

	len = 1;
	int		ten;
	ten = 10;
	while (n > ten)
	{
		len++;
		ten *= 10;
	}
	r = (char *)malloc(len + 1);
	r[len] = 0;
	while (len-- + 1)
	{
		r[len] = n % 10 + '0';
		n = n / 10;
	}
	return (r);
}

void
	sl_displaymap(char **map, void **img, int move)
{
	int	x;
	int	y;
	int	xi;
	int	yi;
	int	c;
	char	*move_str;

	x = 0;
	xi = 0;
	y = -1;
	yi = 0;
	while (map[++y])
	{
		x = -1;
		xi = 0;
		while (map[y][++x])
		{
			c = sl_conv(map[y][x]);
			mlx_put_image_to_window(img[5], img[6], img[c], xi, yi);
			xi += SPRITE_SIZE;
		}
		yi += SPRITE_SIZE;
	}
	printf("x %d , y %d\n", xi, yi);
	mlx_string_put(img[5], img[6], 10, yi + 32, 0x00ff0000, "Move :");
	move_str = ft_itoa(move);
	mlx_string_put(img[5], img[6], 10 + 136, yi + 32, 0x00ff0000, move_str);
	printf("function ITOA of the deadth %s\n", move_str);
	free(move_str);
}

int
	deal_key(int key, void *param)
{
	if (key == KEY_LEFT || key == KEY_A)
		move_player(-1, 0, param);
	else if (key == KEY_DOWN || key == KEY_S)
		move_player(0, 1, param);
	else if (key == KEY_RIGHT || key == KEY_D)
		move_player(1, 0, param);
	else if (key == KEY_UP || key == KEY_W)
		move_player(0, -1, param);
	else if (key == KEY_ESC)
		it_is_the_end(param);
	else
		printf("key pressed : %d\n", key);
	return (0);
}
