#ifndef SL_H
# define SL_H

	//	include

# include	<unistd.h>
# include	<stdlib.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h>
# include	<stdio.h>

# include	"mlx.h"
# include	"mlx_int.h"

typedef struct s_info	t_info;

struct	s_info {
	int		lenght;
	int		width;
	int		px;
	int		py;
	int		coll;
	int		move;
	void	**img;
	char	**map;
};

	//	Constant

# define SPRITE_SIZE 64
# define BUFFER_SIZE 42

# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_W		119

# define KEY_LEFT	65361
# define KEY_DOWN	65364
# define KEY_RIGHT	65363
# define KEY_UP		65362

# define KEY_ESC		65307

	//	get_next_line.c

char	*get_next_line(int fd);

	//	map.c

char	**sl_map(char *s, int *lenght, int *width);

#endif /* SL_H */
