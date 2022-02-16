#	Compilation setting

NAME	=	so_long	
CC		=	gcc

#	Directories

DIR_SRC	=	./srcs
DIR_OBJ	=	./objs

#	Sources

SRCS	=	${DIR_SRC}/main.c	\
		${DIR_SRC}/map.c	\
		${DIR_SRC}/player.c	\
		${DIR_SRC}/brexit.c	\
		${DIR_SRC}/get_next_line.c

OBJS	=	${addprefix ${DIR_OBJ}/, ${notdir ${SRCS:.c=.o}}}

#	Find the os

UNAME_S := $(shell uname -s)


INCLIB	=	/usr/lib

RM		=	rm -f

	#	Linux
ifeq ($(UNAME_S),Linux)
	DIR_LIB_MLX	=	./mlx-linux
	LIB_MLX		+=	-lmlx_linux
	
	DIR_LIB_SYS	=	./usr/lib
	LIB_SYS		+=	-lmlx_Linux
	LIB_SYS		+=	-lXext
	LIB_SYS		+=	-lX11
	LIB_SYS		+=	-lm
	LIB_SYS		+=	-lz
endif

	#	Apple
ifeq ($(UNAME_S),Darwin)
	DIR_LIB_MLX	=	./mlx-apple
	LIB_MLX		+=	-lmlx
endif

vpath %.c ${DIR_SRC}

all : ${NAME}


	#	LINUX Compilation
#	$(CC) $(OBJS) -L${DIR_LIB_MLX}/ -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

	#	APPLE Compilation
#	$(CC) $(OBJS) -L${DIR_LIB_MLX}/ -Imlx -lmlx -o $(NAME)


$(NAME): $(OBJS)
	$(CC) $(OBJS) -L${DIR_LIB_MLX}/ -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	#$(CC) $(OBJS) -L${DIR_LIB_MLX}/ -Imlx-apple -lmlx -o $(NAME)

${DIR_OBJ}/%.o : %.c | ${DIR_OBJ}
	$(CC) -Wall -Wextra -Werror -I/usr/include -I${DIR_LIB_MLX} -O3 -c $< -o $@

${DIR_OBJ} :
	@mkdir -p ${DIR_OBJ}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:		fclean all


norm:
	norminette ${SRCS}
