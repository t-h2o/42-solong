#	Compilation setting

NAME	=	so_long	
CC		=	gcc


#	Directories

DIR_SRC	=	./srcs
DIR_OBJ	=	./objs

DIR_MINILIBX	=	./minilibx-linux
INCLIB			=	/usr/lib

LFLAGS	=	-I${DIR_MINILIBX}		\
			-L${DIR_MINILIBX} -lmlx	\
			-L$(INCLIB) -lXext -lX11 -lm -lbsd

#	Sources

SRCS	=	${DIR_SRC}/main.c		\
			${DIR_SRC}/sl_utils.c	\
			${DIR_SRC}/get_next_line.c

OBJS	=	${addprefix ${DIR_OBJ}/, ${notdir ${SRCS:.c=.o}}}

RM		=	rm -f

vpath %.c ${DIR_SRC}


all : ${NAME}

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L${DIR_MINILIBX}/ -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

${DIR_OBJ}/%.o : %.c | ${DIR_OBJ}
	$(CC) -Wall -Wextra -Werror -I/usr/include -I${DIR_MINILIBX} -O3 -c $< -o $@

${DIR_OBJ} :
	@mkdir -p ${DIR_OBJ}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:		fclean all


norm:
	norminette ${SRCS}

show:
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "SRC		:	$(SRCS)\n"
