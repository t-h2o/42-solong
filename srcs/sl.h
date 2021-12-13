#ifndef SL_H
# define SL_H
# define BUFFER_SIZE 42
	//	include

# include	<unistd.h>
# include	<stdlib.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h>
# include	<stdio.h>

char	*get_next_line(int fd);

#endif /* SL_H */
