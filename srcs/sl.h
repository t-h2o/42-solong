/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:11:08 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/20 16:38:58 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_H
# define SL_H

	//	include

# include	<unistd.h>
# include	<stdlib.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h>
# include	<stdio.h>

# ifdef __APPLE__

#  include	"mlx.h"

# elif __linux__

#  include	"mlx.h"
#  include	"mlx_int.h"

# endif

typedef struct s_info {
	int		lenght;
	int		width;
	int		px;
	int		py;
	int		player;
	int		exit;
	int		coll;
	int		move;
	void	**img;
	char	**map;
}	t_info;

	//	Constant

# define SPRITE_SIZE 64
# define BUFFER_SIZE 42
# define COLOR	0x00ff0000

# ifdef __APPLE__

#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define KEY_W		13

#  define KEY_LEFT		123
#  define KEY_DOWN		125
#  define KEY_RIGHT		124
#  define KEY_UP		126
#  define KEY_ESC		53

# elif __linux__

#  define KEY_A			97
#  define KEY_S			115
#  define KEY_D			100
#  define KEY_W			119

#  define KEY_LEFT		65361
#  define KEY_DOWN		65364
#  define KEY_RIGHT		65363
#  define KEY_UP		65362
#  define KEY_ESC		65307

# endif

	//	get_next_line.c

char	*get_next_line(int fd);

	//	map.c

void	sl_map(t_info *info, char *file);

	//	brexit.c

void	it_is_the_end(t_info *param, int option, char *msg);
int		it_is_the_end_red_cross(t_info *info);

	//	player.c

int		deal_key(int key, void *param);
void	sl_displaymap(char **map, void **img, int move, int coll);

	//	info.c

void	info_map(t_info *info);

#endif /* SL_H */
