#include	"sl.h"

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

	img[5] = mlx_init();
	img[6] = mlx_new_window(img[5], 1920, 1080, "So long!");
	img[0] = mlx_xpm_file_to_image(img[5], "./Assets/empty.xpm", &img_width, &img_height);
	img[1] = mlx_xpm_file_to_image(img[5], "./Assets/wall.xpm", &img_width, &img_height);
	img[2] = mlx_xpm_file_to_image(img[5], "./Assets/player.xpm", &img_width, &img_height);
	img[3] = mlx_xpm_file_to_image(img[5], "./Assets/collectible.xpm", &img_width, &img_height);
	img[4] = mlx_xpm_file_to_image(img[5], "./Assets/exit.xpm", &img_width, &img_height);
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
		printf("%s", map[y]);
		y++;
	}

	sl_displaymap(map, img);
	
	while (*map)
	{	
		printf("free(%p) : %s", *map, *map);
		free(*(map++));
	}
	mlx_loop(img[5]);
}
