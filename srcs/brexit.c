/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brexit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tgrivel@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:34:05 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/16 14:02:03 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"sl.h"

static void
	free_map(char **map)
{
	int		i;

	i = 0;
	while (i < 16 && map[i])
	{	
		printf("%.2d | free(%p) : %s\n", i, map[i], map[i]);
		free(map[i++]);
	}
	free(map);
	printf("free the tab of line\n");
}
/*	Free each line
 *	free tab of line
 */

void
	it_is_the_end(t_info *param, int option, char *msg)
{
	void	**img;

	printf("%s\n", msg);
	if (option)
		free_map(param->map);
	img = param->img;
	if (option == 2)
		printf("destroy the window");
	if (option == 2)
		mlx_destroy_window(img[5], img[6]);
	printf("free(%p) : img\n", img);
	free(param->img);
	exit(0);
}
/*	option 0
 *		free img
 *	option 1
 *		free tab
 *		free img
 *	option 2
 *		free tab
 *		destroy window
 *		free img
 */
