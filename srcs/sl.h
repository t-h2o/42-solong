#ifndef SL_H
# define SL_H

	//	Constant

# define	SPRITE_SIZE 64
# define	BUFFER_SIZE 42

# define	KEY_A		97
# define	KEY_S		115
# define	KEY_D		100
# define	KEY_W		119

# define	KEY_LEFT	65361
# define	KEY_DOWN	65364
# define	KEY_RIGHT	65363
# define	KEY_UP		65362

# define	KEY_ESC		65307

	//	include

# include	<unistd.h>
# include	<stdlib.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h>
# include	<stdio.h>

#include	"mlx.h"
#include	"mlx_int.h"

char	*get_next_line(int fd);
int		sl_strlen(char *s);

#endif /* SL_H */
