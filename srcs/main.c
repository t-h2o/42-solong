#include	"mlx.h"
#include	"mlx_int.h"

int
	main(void)
{
	void	*mlx;
	void	*mlx_win;
	void	*img;

	char	*relative_path = "./Assets/texture.xpm";
	int		img_width;
	int		img_height;


	mlx = mlx_init();

	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");

	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);

	int	pol = 500;
	while (pol++ < 1000)	
		mlx_pixel_put(mlx, mlx_win, pol, 500,  0x12344532);

	mlx_put_image_to_window(mlx, mlx_win, img, 0, 0);
	
	mlx_loop(mlx);
}
