#include "cub3d.h"

void	ft_player_hook(void *param)
{
	t_game	*game;
	float	angle_to_add;
	float	ray_angle;
	int		ray_count;

	game = (t_game *)param;
	handle_movement(game, game->player_data);
	clear_image(game);
	draw_square(game->player_data->x, game->player_data->y, 4, game);
	angle_to_add = (ANGLE_OF_VIEW * PI / 180) / WIDTH;
	ray_angle = game->player_data->angle - (ANGLE_OF_VIEW * PI / 180) / 2;
	ray_count = 0;
	while (ray_count < WIDTH)
	{
		draw_single_ray(game, game->player_data, ray_angle, ray_count);
		ray_angle = ray_angle + angle_to_add;
		ray_count++;
	}
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

int	main(void)
{
	t_game *game;

	game = initialize_game_data();
	// mlx_key_hook(game->mlx, key_hook, game);
	// mlx_loop_hook(game->mlx, ft_player_hook, game);
	// mlx_image_to_window(game->mlx, game->player_data->player, 0, 0);
	// mlx_loop(game->mlx);
	// mlx_terminate(game->mlx);
	return (0);
}