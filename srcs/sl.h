#ifndef SL_H
# define SL_H

	//	Constant

# define	SPRITE_SIZE 64
# define	BUFFER_SIZE 42

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
