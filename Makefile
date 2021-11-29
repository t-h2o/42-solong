NAME			=	game_theo
SRC_MINILIBX	=	./minilibx-linux/

SRC_DIR			=	./srcs
OBJ_DIR			=	./objs

SRCS			=	${SRC_DIR}/main.c

CC				=	gcc
FLAGS			=	-Wall -Werror -Wextra

LIB				=	-I /usr/include
LIBA			=	-L /usr/lib -lmlx -framework OpenGL -framework AppKit


# gcc -I/usr/include -O3 -I.. -g   -c -o main.o main.c
# gcc -o mlx-test main.o -L.. -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd

${NAME}:	${SRCS}
	gcc ${SRCS}

all:	${NAME}
