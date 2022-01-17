#include	"sl.h"

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
	printf("x %d , y %d\n", xi, yi);
	mlx_string_put(img[5], img[6], 10, yi + 32, 0x00ff0000, "Move :");
	mlx_string_put(img[5], img[6], 10 + 36, yi + 32, 0x00ff0000, "42");
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
	sl_ptr(void ** img, int lenght, int width)
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
	printf("\n\nWINDOW SIZE %d x %d\n\n", lenght * 64, width * 64);
	img[6] = mlx_new_window(img[5], lenght * 64, width * 64, "So long!");
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
	s_info	info;

	if (argc != 2)
		return (0);
	map = sl_map(argv[1], &info.lenght, &info.width);
	if (!map)
		return (0);

	printf("\n\nWINDOW SIZE : %d x %d\n\n", info.lenght, info.width);
	sl_ptr(img, info.lenght, info.width);
	int	y;

	y = 0;
	
	while (map[y])
	{
		printf("%s\n", map[y]);
		y++;
	}

	sl_displaymap(map, img);

	find_player(map, &info.px, &info.py, &info.coll);
	info.map = map;
	info.img = img;
	info.move = 0;
	mlx_key_hook(img[6], deal_key, (void *)&info);
	mlx_loop(img[5]);
}
