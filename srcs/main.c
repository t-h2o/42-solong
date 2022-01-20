#include	"sl.h"

static void
	sl_ptr(void **img, int lenght, int width)
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
	find_player(char **map, int *x, int *y, int *coll)
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
	main(int argc, char **argv)
{
	void	*img[7];
	char	**map;
	int		y;
	t_info	info;

	if (argc != 2)
		return (0);
	map = sl_map(argv[1], &info.lenght, &info.width);
	if (!map)
		return (0);

	printf("\n\nWINDOW SIZE : %d x %d\n\n", info.lenght, info.width);
	sl_ptr(img, info.lenght, info.width);

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
