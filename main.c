#include "cub3d.h"

static mlx_image_t	*background;
static mlx_image_t	*wall;

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
}

void	move_player(t_point *player_coords)
{
	int		speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player_coords->angle);
	sin_angle = sin(player_coords->angle);
	angle_speed = 0.1;
	speed = 5;
	if (player_coords->left_rotate)
	{
		player_coords->angle = player_coords->angle - angle_speed;
	}
	if (player_coords->right_rotate)
	{
		player_coords->angle = player_coords->angle + angle_speed;
	}
	if (player_coords->angle > 2 * PI)
	{
		player_coords->angle = 0;
	}
	if (player_coords->angle < 0)
	{
		player_coords->angle = 2 * PI;
	}
	if (player_coords->key_up)
	{
		player_coords->x = player_coords->x + (cos_angle * speed);
		player_coords->y = player_coords->y + (sin_angle * speed);
	}
	if (player_coords->key_down)
	{
		player_coords->x = player_coords->x - (cos_angle * speed);
		player_coords->y = player_coords->y - (sin_angle * speed);
	}
	if (player_coords->key_left)
	{
		player_coords->x = player_coords->x + (sin_angle * speed);
		player_coords->y = player_coords->y - (cos_angle * speed);
	}
	if (player_coords->key_right)
	{
		player_coords->x = player_coords->x - (sin_angle * speed);
		player_coords->y = player_coords->y + (cos_angle * speed);
	}
}

void	clear_image(t_game *game)
{
	if (!game->player || !game->player->pixels)
		return ;
	ft_bzero(game->player->pixels, game->player->width * game->player->height
		* sizeof(int));
}

void	draw_square(float x, float y, int size, t_game *game)
{
	uint32_t	color;
	int			i;

	color = (uint32_t)ft_pixel(255, 255, 0, 255);
	i = -1;
	while (++i < size)
		mlx_put_pixel(game->player, x + i, y, color);
	i = -1;
	while (++i < size)
		mlx_put_pixel(game->player, x, y + i, color);
	i = -1;
	while (++i < size)
		mlx_put_pixel(game->player, x + size, y + i, color);
	i = -1;
	while (++i < size)
		mlx_put_pixel(game->player, x + i, y + size, color);
}

bool	cast_ray(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / OBJECT;
	y = py / OBJECT;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

void	ft_player_hook(void *param)
{
	t_game	*game;
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;

	uint32_t	color;
	color = (uint32_t)ft_pixel(255, 255, 0, 255);

	game = (t_game *)param;
	move_player(game->player_coords);
	clear_image(game);
	draw_square(game->player_coords->x, game->player_coords->y, 12, game);
	ray_x = game->player_coords->x;
	ray_y = game->player_coords->y;
	cos_angle = cos(game->player_coords->angle);
	sin_angle = sin(game->player_coords->angle);

	while(!cast_ray(ray_x, ray_y, game))
	{
		// put_pixel(ray_x, ray_y, 0xFF0000, game);
		mlx_put_pixel(game->player, ray_x, ray_y, color);
		ray_x = cos_angle + ray_x;
		ray_y = sin_angle + ray_y;
	}
	// mlx_image_to_window(game->mlx, game->player,
	// game->player_coords->x,game->player_coords->y);
}

char				map[12][12] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', 'N', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

static void	handle_key_press(struct mlx_key_data keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_W)
		game->player_coords->key_up = true;
	if (keydata.key == MLX_KEY_S)
		game->player_coords->key_down = true;
	if (keydata.key == MLX_KEY_A)
		game->player_coords->key_left = true;
	if (keydata.key == MLX_KEY_D)
		game->player_coords->key_right = true;
	if (keydata.key == MLX_KEY_LEFT)
		game->player_coords->left_rotate = true;
	if (keydata.key == MLX_KEY_RIGHT)
		game->player_coords->right_rotate = true;
	// if (keydata.key == MLX_KEY_ESCAPE)
	// {
	// 	free_map(game->map);
	// 	destroy_cub3d(game->mlx, 0);
	// }
}

static void	handle_key_release(struct mlx_key_data keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_W)
		game->player_coords->key_up = false;
	if (keydata.key == MLX_KEY_S)
		game->player_coords->key_down = false;
	if (keydata.key == MLX_KEY_A)
		game->player_coords->key_left = false;
	if (keydata.key == MLX_KEY_D)
		game->player_coords->key_right = false;
	if (keydata.key == MLX_KEY_LEFT)
		game->player_coords->left_rotate = false;
	if (keydata.key == MLX_KEY_RIGHT)
		game->player_coords->right_rotate = false;
}

void	key_hook(struct mlx_key_data keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS)
		handle_key_press(keydata, game);
	if (keydata.action == MLX_RELEASE)
		handle_key_release(keydata, game);
}

void	init_player(t_point *player_coords)
{
	player_coords->x = WIDTH / 2;
	player_coords->y = HEIGHT / 2;
	player_coords->angle = PI / 2;
	player_coords->key_up = false;
	player_coords->key_down = false;
	player_coords->key_left = false;
	player_coords->key_right = false;
	player_coords->left_rotate = false;
	player_coords->right_rotate = false;
}

int	main(void)
{
	t_game *game;

	game = malloc(1 * sizeof(t_game));
	game->player_coords = malloc(sizeof(t_point));
	init_player(game->player_coords);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			game->map[i][j] = map[i][j];
		}
	}
	game->player = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	flood_map_items(game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, ft_player_hook, game);
	mlx_image_to_window(game->mlx, game->player, 0, 0);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (0);
}