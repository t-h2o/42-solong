/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:17:02 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/21 13:40:24 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"sl.h"

static void
	sl_ptr(void **img, int lenght, int width)
{
	int		img_width;
	int		img_height;

	img[5] = mlx_init();
	img[6] = mlx_new_window(img[5], lenght * 64, width * 64, "So long!");
	img[0] = mlx_xpm_file_to_image(img[5], "./assets/empty.xpm",
			&img_width, &img_height);
	img[1] = mlx_xpm_file_to_image(img[5], "./assets/wall.xpm",
			&img_width, &img_height);
	img[2] = mlx_xpm_file_to_image(img[5], "./assets/player.xpm",
			&img_width, &img_height);
	img[3] = mlx_xpm_file_to_image(img[5], "./assets/collectible.xpm",
			&img_width, &img_height);
	img[4] = mlx_xpm_file_to_image(img[5], "./assets/exit.xpm",
			&img_width, &img_height);
	img[7] = mlx_xpm_file_to_image(img[5], "./assets/info.xpm",
			&img_width, &img_height);
}
/*	to not be longer than 80 caracters,
 *	I set a tab of paths...
 *	This function set my tab of image
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
	info_map(info);
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
	mlx_hook(info.img[6], 17, 1L, it_is_the_end_red_cross, &info);
	mlx_loop(info.img[5]);
}
/*	check arguments
 *	init info game
 *	display map once
 *	init key hook
 *	loop
 */
