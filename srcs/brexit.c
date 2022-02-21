/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brexit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tgrivel@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:34:05 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/21 13:32:55 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"sl.h"

static void
	free_map(char **map)
{
	int		i;

	i = 0;
	while (i < 16 && map[i])
		free(map[i++]);
	free(map);
}
/*	Free each line
 *	free tab
 */

int
	it_is_the_end_red_cross(t_info *info)
{
	it_is_the_end(info, 2, "red cross pressed");
	return (0);
}

void
	it_is_the_end(t_info *param, int option, char *msg)
{
	void	**img;

	printf("\n\n\t--- stop message  ---\n");
	printf("\t%s\n", msg);
	printf("\t---------------------\n\n");
	if (option)
		free_map(param->map);
	img = param->img;
	if (option == 2)
		mlx_destroy_window(img[5], img[6]);
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
