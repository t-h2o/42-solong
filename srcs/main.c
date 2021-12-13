#include	"mlx.h"
#include	"mlx_int.h"
#include	"sl.h"

static int
	sl_strlen(char *s)
{
	int	r;

	r = 0;
	while (s[r])
		r++;
	return (r);
}

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
	main(int argc, char ** argv)
{
	if (argc != 2)
		return (0);
	
	void	*mlx;
	void	*mlx_win;

	void	*img_wall;
	void	*img_empt;
	void	*img_coll;
	void	*img_exit;
	void	*img_play;

	int		img_width;
	int		img_height;
	

	char	**map;
	
	map = sl_map(argv[1]);
	if (!map)
		return (0);

	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, 1920, 1080, "So long!");

	img_wall = mlx_xpm_file_to_image(mlx, "./Assets/wall.xpm", &img_width, &img_height);
	img_empt = mlx_xpm_file_to_image(mlx, "./Assets/empty.xpm", &img_width, &img_height);
	img_coll = mlx_xpm_file_to_image(mlx, "./Assets/collectible.xpm", &img_width, &img_height);
	img_exit = mlx_xpm_file_to_image(mlx, "./Assets/exit.xpm", &img_width, &img_height);
	img_play = mlx_xpm_file_to_image(mlx, "./Assets/player.xpm", &img_width, &img_height);

	int	x;
	int	y;
	int	len;

	y = 0;
	while (1)
	{
		x = 0;
		if (!map[y / SPRITE_SIZE])
			break ;
		len = sl_strlen(map[y / SPRITE_SIZE]) - 1;
		printf("\nlen : %d\n", len);
		while (map[y / SPRITE_SIZE][x / SPRITE_SIZE])
		{
			char	*getLine = &map[y / SPRITE_SIZE][x / SPRITE_SIZE];
			if ((x == 0 || y == 0) && *getLine != '1')
				printf("hole...\tX : %d\tY : %d\n", x / SPRITE_SIZE, y / SPRITE_SIZE);
			if (*getLine == 'E')
				mlx_put_image_to_window(mlx, mlx_win, img_exit, x, y);
			if (*getLine == 'C')
				mlx_put_image_to_window(mlx, mlx_win, img_coll, x, y);
			if (*getLine == '1')
			{
				mlx_put_image_to_window(mlx, mlx_win, img_wall, x, y);
				printf("WALL...\tX : %d\tY : %d\n", x / SPRITE_SIZE, y / SPRITE_SIZE);
			}
			if (*getLine == '0')
				mlx_put_image_to_window(mlx, mlx_win, img_empt, x, y);
			if (*getLine == 'P')
				mlx_put_image_to_window(mlx, mlx_win, img_play, x, y);
			getLine++;
			x += SPRITE_SIZE;
		}

		y += SPRITE_SIZE;
	}
	while (*map)
	{	
		printf("free(%p) : %s", *map, *map);
		free(*(map++));
	}
	mlx_loop(mlx);
}
