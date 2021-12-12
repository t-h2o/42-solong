INCLIB	=	/usr/lib

#	Compilation setting

NAME	=	so_long	

CC		=	gcc


#	Directories

DIR_SRC	=	./srcs
DIR_OBJ	=	./objs

DIR_MINILIBX	=	./minilibx-linux

LFLAGS	=	-I${DIR_MINILIBX} \
			-L${DIR_MINILIBX} \
			-lmlx -L$(INCLIB) \
			-lXext -lX11 -lm -lbsd


#	Sources

SRCS	=	${DIR_SRC}/main.c

OBJS	=	${addprefix ${DIR_OBJ}/, ${notdir ${SRCS:.c=.o}}}

RM		=	rm -f

vpath %.c ${DIR_SRC}


all : ${NAME}

${NAME}:	${OBJS}
	${CC} -o ${NAME}  ${OBJS} ${LFLAGS}

${DIR_OBJ}/%.o : %.c | ${DIR_OBJ}
	${CC} -o $@ -c $^ ${LFLAGS}

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
