/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:17:02 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/16 12:44:32 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"sl.h"

static void
	sl_ptr(void **img, int lenght, int width)
{
	int		img_width;
	int		img_height;
	char	*path[6];

	path[0] = "./Assets/empty.xpm";
	path[1] = "./Assets/wall.xpm";
	path[2] = "./Assets/player.xpm";
	path[3] = "./Assets/collectible.xpm";
	path[4] = "./Assets/exit.xpm";
	path[5] = "./Assets/info.xpm";
	img[5] = mlx_init();
	img[6] = mlx_new_window(img[5], lenght * 64, width * 64, "So long!");
	img[0] = mlx_xpm_file_to_image(img[5], path[0], &img_width, &img_height);
	img[1] = mlx_xpm_file_to_image(img[5], path[1], &img_width, &img_height);
	img[2] = mlx_xpm_file_to_image(img[5], path[2], &img_width, &img_height);
	img[3] = mlx_xpm_file_to_image(img[5], path[3], &img_width, &img_height);
	img[4] = mlx_xpm_file_to_image(img[5], path[4], &img_width, &img_height);
	img[7] = mlx_xpm_file_to_image(img[5], path[5], &img_width, &img_height);
}
/*	to not be longer than 80 caracters,
 *	I set a tab of paths...
 *	This function set my tab of image
 */

void
	find_player(char **map, int *x, int *y, int *coll)
{
	int	line;
	int	colo;
	int	doorexit;
	int	nbplayer;

	nbplayer = 0;
	line = 0;
	*coll = 0;
	doorexit = 0;
	while (map[line])
	{
		colo = 0;
		while (map[line][colo])
		{
			if (map[line][colo] == 'C')
				(*coll)++;
			if (map[line][colo] == 'E')
				doorexit++;
			if (map[line][colo] == 'P')
			{
				if (nbplayer)
				{
					printf("Error, there is more than 1 player\n");
					exit(0);
				}
				*x = colo;
				*y = line;
				nbplayer = 1;
			}
			colo++;
		}
		line++;
	}
	if (!coll || !doorexit)
	{
		printf("Error, there is 0 item or 0 exit door\n");
		exit(0);
	}
}
/*	Give the position of the player by x and y.
 *	Give the number of collectible in the map
 */

static void
	init_info(t_info *info, char *argv)
{
	info->img = (void **)malloc(sizeof(void *) * 9);
	if (!info->img)
		exit (0);
	info->img[8] = 0;
	sl_map(info, argv);
	sl_ptr(info->img, info->lenght, info->width);
	find_player(info->map, &info->px, &info->py, &info->coll);
	info->move = 0;
}
/*	Set info data
 *	if the 1st malloc fail, exit
 */

int
	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 2)
		printf("Error, bad number of argument\n");
	if (argc != 2)
		return (0);
	init_info(&info, argv[1]);
	sl_displaymap(info.map, info.img, 0, info.coll);
	mlx_key_hook(info.img[6], deal_key, (void *)&info);
	mlx_loop(info.img[5]);
}
/*	check arguments
 *	init info game
 *	display map once
 *	init key hook
 *	loop
 */
