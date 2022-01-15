#include	"sl.h"

typedef struct struct_info s_info;

struct	struct_info {
	int	px;
	int py;
	int coll;
	int	move;
	void **img;
	char ** map;
};

static char
	**sl_map(char *s)
{
	int		fd;
	int		n;
	int		i;
	char	*l;
	char	**r;

	fd = open(s, O_RDONLY);
	n = 0;
	l = (char *) 1;
	while (l)
	{
		l = get_next_line(fd);
		free(l);
		n++;
	}
	printf("\n\nLINE : %d\n\n", n);
	close(fd);
	r = malloc(sizeof(char *) * n);
	if (!r)
		return (0);
	r[n] = 0;
	fd = open(s, O_RDONLY);
	i = 0;
	while (i < n)
		r[i++] = get_next_line(fd);
	close(fd);
	return (r);
}

int
	sl_conv(char c)
{
	if (c == 'E')
		return (4);
	if (c == 'C')
		return (3);	
	if (c == 'P')
		return (2);
	return(c - '0');
}

void
	sl_displaymap(char ** map, void ** img)
{
	int	x;
	int	y;
	int	xi;
	int	yi;
	int	c;

	x = 0;
	xi = 0;
	y = -1;
	yi = 0;
	while (map[++y])
	{
		x = -1;
		xi = 0;
		while (map[y][++x])
		{
			c = sl_conv(map[y][x]);
			if (c != -38)
				mlx_put_image_to_window(img[5], img[6], img[c], xi, yi);
			xi += SPRITE_SIZE;
		}
		yi += SPRITE_SIZE;
	}
}
	/*
	0 empt
	1 wall
	2 play
	3 coll
	4 exit
	5 MLX
	6 MLX_WIN
	*/

static void
	sl_ptr(void ** img)
{
	int		img_width;
	int		img_height;
	char	*path[5];

	path[0] = "./Assets/empty.xpm";
	path[1] = "./Assets/wall.xpm";
	path[2] = "./Assets/player.xpm";
	path[3] = "./Assets/collectible.xpm";
	path[4] = "./Assets/exit.xpm";
	img[5] = mlx_init();
	img[6] = mlx_new_window(img[5], 1920, 1080, "So long!");
	img[0] = mlx_xpm_file_to_image(img[5], path[0], &img_width, &img_height);
	img[1] = mlx_xpm_file_to_image(img[5], path[1], &img_width, &img_height);
	img[2] = mlx_xpm_file_to_image(img[5], path[2], &img_width, &img_height);
	img[3] = mlx_xpm_file_to_image(img[5], path[3], &img_width, &img_height);
	img[4] = mlx_xpm_file_to_image(img[5], path[4], &img_width, &img_height);
}

void
	it_is_the_end(s_info * param)
{
	char ** map = param->map;
	while (*map)
	{	
		printf("free(%p) : %s\n", *map, *map);
		free(*(map++));
	}
	
	void ** img = param->img;
	mlx_destroy_window(img[5], img[6]);
	exit(0);
}

void
	move_player(int movex, int movey, s_info * param)
{
	printf("coll : %d\n", param->coll);
	if (param->map[param->py + movey][param->px + movex] == '1')
		return ;
	if (param->map[param->py + movey][param->px + movex] == 'E')
	{
		if (!param->coll)
			it_is_the_end(param);
		return ;	
	}
	if (param->map[param->py + movey][param->px + movex] == 'C')
		param->coll--;
	param->move++;
	printf("move number : %d\n", param->move);
	param->map[param->py][param->px] = '0';
	param->px += movex;
	param->py += movey;
	param->map[param->py][param->px] = 'P';
	sl_displaymap(param->map, param->img);
}

int
	deal_key(int key, void * param)
{
	if (key == KEY_LEFT || key == KEY_A)
		move_player(-1 , 0, param);
	else if (key == KEY_DOWN || key == KEY_S)
		move_player(0, 1, param);
	else if (key == KEY_RIGHT || key == KEY_D)
		move_player(1, 0, param);
	else if (key == KEY_UP || key == KEY_W)
		move_player(0, -1, param);
	else if (key == KEY_ESC)
		it_is_the_end(param);
	else
		printf("key pressed : %d\n", key);
	return (0);
}

void
	find_player(char ** map, int * x, int * y, int * coll)
{
	int	line;
	int	colo;
	
	line = 0;
	*coll = 0;
	while (map[line])
	{
		colo = 0;
		while (map[line][colo])
		{
			if (map[line][colo] == 'C')
				(*coll)++;
			if (map[line][colo] == 'P')
			{
				*x = colo;
				*y = line;
			}
			colo++;
		}
		line++;	
	}
}

int
	main(int argc, char ** argv)
{
	void	*img[7];
	char	**map;

	if (argc != 2)
		return (0);
	map = sl_map(argv[1]);
	if (!map)
		return (0);
	sl_ptr(img);
	int	y;

	y = 0;
	
	while (map[y])
	{
		printf("%s\n", map[y]);
		y++;
	}

	sl_displaymap(map, img);
	
	s_info info;
	find_player(map, &info.px, &info.py, &info.coll);
	info.map = map;
	info.img = img;
	info.move = 0;
	mlx_key_hook(img[6], deal_key, (void *)&info);
	mlx_loop(img[5]);
}
