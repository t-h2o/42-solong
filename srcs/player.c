/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:18:05 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/16 12:39:33 by tgrivel          ###   ########.fr       */
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
/*	0 empt
	1 wall
	2 play
	3 coll
	4 exit
	5 MLX
	6 MLX_WIN
*/


static void
	move_player(int movex, int movey, t_info *param)
{
	if (param->map[param->py + movey][param->px + movex] == '1')
		return ;
	if (param->map[param->py + movey][param->px + movex] == 'E')
	{
		if (!param->coll)
			it_is_the_end(param, 1, "Erro, 0 collectible");
		return ;
	}
	if (param->map[param->py + movey][param->px + movex] == 'C')
		param->coll--;
	param->move++;
	param->map[param->py][param->px] = '0';
	param->px += movex;
	param->py += movey;
	param->map[param->py][param->px] = 'P';
	sl_displaymap(param->map, param->img, param->move, param->coll);
}

char
	*ft_itoa(int n)
{
	char	*r;
	int		len;
	int		ten;

	len = 1;
	ten = 10;
	while (n >= ten)
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
/*	Return a string with a number
 */

void
	sl_displaymap(char **map, void **img, int move, int coll)
{
	int	x;
	int	y;
	int	c;

	x = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			c = sl_conv(map[y][x]);
			mlx_put_image_to_window(img[5], img[6], img[c], x * 64, y * 64);
		}
	}
	while (x--)
		mlx_put_image_to_window(img[5], img[6], img[7], x * 64, y * 64);
	mlx_string_put(img[5], img[6], 10, y * 64 + 37, COLOR, "Move :");
	mlx_string_put(img[5], img[6], 10 + 36, y * 64 + 37, COLOR, ft_itoa(move));
	mlx_string_put(img[5], img[6], 64, y * 64 + 37, COLOR, "Item :");
	mlx_string_put(img[5], img[6], 64 + 36, y * 64 + 37, COLOR, ft_itoa(coll));
}
/*	Every move of the player,
 *	the map is refresh...
 */

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
		it_is_the_end(param, 1, "ESC pressed");
	else
		printf("key pressed : %d\n", key);
	return (0);
}
/*	send to a function by the key
 */
