#include "cub3d.h"

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
	uint32_t	grey;
	uint32_t	white_color;

	background = mlx_new_image(game->mlx, WIDTH / 12, WIDTH / 12);
	wall = mlx_new_image(game->mlx, WIDTH / 12, WIDTH / 12);
	grey = (uint32_t)ft_pixel(50, 50, 50, 255);
	for (uint32_t i = 0; i < background->width; ++i)
	{
		for (uint32_t j = 0; j < background->height; ++j)
		{
			mlx_put_pixel(background, i, j, grey);
		}
	}
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
			if (game->map[y][x] == '0')
				mlx_image_to_window(game->mlx, background, x * WIDTH / 12, y
					* HEIGHT / 12);
			x++;
		}
		y++;
	}
}

void	ft_randomize(void *param)
{
	uint32_t	color;
	t_game		*game;

	game = (t_game *)param;
	color = (uint32_t)ft_pixel(255, 255, 0, 255);
	for (uint32_t i = 0; i < game->player->width; ++i)
	{
		for (uint32_t y = 0; y < game->player->height; ++y)
		{
			mlx_put_pixel(game->player, i, y, color);
		}
	}
}

void	ft_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->player->instances[0].y -= 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->player->instances[0].y += 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player->instances[0].x -= 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player->instances[0].x += 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	// 	image->instances[0].x += 5;
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
	t_game	*game;

	game = malloc(1 * sizeof(t_game));
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			game->map[i][j] = map[i][j];
		}
	}
	game->player = mlx_new_image(game->mlx, 12, 12);
	flood_map_items(game);
	mlx_image_to_window(game->mlx, game->player, 0, 0);
	mlx_loop_hook(game->mlx, ft_randomize, game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (0);
}

// void	put_pixel(int x, int y, int color, t_game *game)
// {
// 	int	index;

// 	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
// 		return ;
// 	index = y * game->size_line + x * game->bpp / 8;
// 	game->data[index] = color & 0xFF;
// 	game->data[index + 1] = (color >> 8) & 0xFF;
// 	game->data[index + 2] = (color >> 16) & 0xFF;
// }

// void draw_square(int x, int y, int size, int color, t_game *game)
// {
// 	int i;

// 	i = 0;
// 	while(i < size)
// 	{
// 		put_pixel(x + i, y, color, game);
// 		i++;
// 	}
// 	i = 0;
// 	while(i < size)
// 	{
// 		i++;
// 		put_pixel(x, y + i, color, game);
// 	}
// 	i = 0;
// 	while(i < size)
// 	{
// 		i++;
// 		put_pixel(x + size, y + i, color, game);
// 	}
// 	i = 0;
// 	while(i < size)
// 	{
// 		i++;
// 		put_pixel(x + i, y + size, color, game);
// 	}
// }

// void	init_game(t_game *game)
// {
// 	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
// 	// game->win = mlx_new_;
// 	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
// 	game->data = (int *)mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
// 	mlx_image_to_window(game->mlx, game->img, 0, 0);
// }

// int	main(void)
// {
// 	t_game *game;

// 	game = malloc(1 * sizeof(t_game));
// 	init_game(game);
// 	draw_square(WIDTH / 2, HEIGHT / 2, 10, 0x00FF00, game);
// 	mlx_loop(game->mlx);
// 	return (0);
// }