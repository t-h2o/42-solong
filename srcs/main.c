#include	"mlx.h"
#include	"mlx_int.h"
#include	"sl.h"

int
	main(void)
{
	void	*mlx;
	void	*mlx_win;

	void	*img_wall;
	void	*img_empt;
	void	*img_coll;
	void	*img_exit;
	void	*img_play;

	int		img_width;
	int		img_height;


	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, 1920, 1080, "So long!");


	img_wall = mlx_xpm_file_to_image(mlx, "./Assets/wall.xpm", &img_width, &img_height);
	img_empt = mlx_xpm_file_to_image(mlx, "./Assets/empty.xpm", &img_width, &img_height);
	img_coll = mlx_xpm_file_to_image(mlx, "./Assets/collectible.xpm", &img_width, &img_height);
	img_exit = mlx_xpm_file_to_image(mlx, "./Assets/exit.xpm", &img_width, &img_height);
	img_play = mlx_xpm_file_to_image(mlx, "./Assets/player.xpm", &img_width, &img_height);


//mlx_pixel_put(mlx, mlx_win, 300, 500,  0x12344532);


	int		fd_ber;
	fd_ber = open("./map.ber", O_RDONLY);
	int		line;
	
	char	*getLine;
	
	line = 0;
	while (line++ < 5)
		printf("%d\t|\t%s", line, get_next_line(fd_ber));
	int	x;
	int	y;
	x = 0;
	y = 0;
	while (1)
	{
		getLine = get_next_line(fd_ber);
		if (!getLine)
			break ;
		while (*getLine)
		{
			if (*getLine == 'E' || *getLine == 'C')
				mlx_put_image_to_window(mlx, mlx_win, img_exit, x, y);
			if (*getLine == 'C')
				mlx_put_image_to_window(mlx, mlx_win, img_coll, x, y);
			if (*getLine == '1')
				mlx_put_image_to_window(mlx, mlx_win, img_wall, x, y);
			if (*getLine == '0')
				mlx_put_image_to_window(mlx, mlx_win, img_empt, x, y);
			if (*getLine == 'P')
				mlx_put_image_to_window(mlx, mlx_win, img_play, x, y);
			getLine++;
			x += 64;
		}
		y += 64;
		x = 0;
	}
	close(fd_ber);
	


	
	mlx_loop(mlx);
}
