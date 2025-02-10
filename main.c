#include "cub3d.h"

static mlx_image_t	*image;
static mlx_image_t	*background;
static mlx_image_t	*wall;

// void	flood_map_items(t_game *game)
// {
// 	int	y;
// 	int	x;

// 	background = mlx_new_image(game->mlx, 24, 24);
// 	wall = mlx_new_image(game->mlx, 24, 24);
// 	y = 0;
// 	while (y < 9)
// 	{
// 		x = 0;
// 		while (x < 9)
// 		{
// 			if (game->map[y][x] == '1')
// 				mlx_image_to_window(game->mlx, background, 0, 0);
// 			if (game->map[y][x] == '0')
// 				mlx_image_to_window(game->mlx, wall, 0, 0);
// 			x++;
// 		}
// 		y++;
// 	}
// }

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	flood_map_items(t_game *game)
{
	int			y;
	int			x;
	uint32_t	green_color;
	uint32_t	white_color;

	background = mlx_new_image(game->mlx, WIDTH / 12, WIDTH / 12);
	wall = mlx_new_image(game->mlx, WIDTH / 12, WIDTH / 12);
	// Fill background image with green color
	green_color = (uint32_t)ft_pixel(0, 255, 0, 255);
	for (uint32_t i = 0; i < background->width; ++i)
	{
		for (uint32_t j = 0; j < background->height; ++j)
		{
			mlx_put_pixel(background, i, j, green_color);
		}
	}
	// Fill wall image with white color
	white_color = (uint32_t)ft_pixel(255, 255, 255, 255);
	for (uint32_t i = 0; i < wall->width; ++i)
	{
		for (uint32_t j = 0; j < wall->height; ++j)
		{
			mlx_put_pixel(wall, i, j, white_color);
		}
	}
	y = 0;
	while (y < 12)
	{
		x = 0;
		while (x < 12)
		{
			if (game->map[y][x] == '1')
				mlx_image_to_window(game->mlx, wall, x * WIDTH / 12, y * HEIGHT
					/ 12);
			// if (game->map[y][x] == '0')
			// 	mlx_image_to_window(game->mlx, background, x * WIDTH / 9, y
			// 		* HEIGHT / 9);
			x++;
		}
		y++;
	}
}

void	ft_randomize(void *param)
{
	uint32_t	color;

	(void)param;
	color = (uint32_t)ft_pixel(255, 255, 0, 255);
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

char				map[12][12] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
};
int	main(void)
{
	t_game *game;

	game = malloc(1 * sizeof(t_game));
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			game->map[i][j] = map[i][j];
		}
	}
	image = mlx_new_image(game->mlx, 12, 12);
	flood_map_items(game);
	mlx_image_to_window(game->mlx, image, 0, 0);
	mlx_loop_hook(game->mlx, ft_randomize, game->mlx);
	mlx_loop_hook(game->mlx, ft_hook, game->mlx);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (0);
}