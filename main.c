/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:20:16 by macbook           #+#    #+#             */
/*   Updated: 2025/04/02 22:53:38 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_cub_file(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		printf("Error:\n Map file must have a .cub extension\n");
		return (1);
	}
	return (0);
}

void	ft_player_hook(void *param)
{
	t_game	*game;
	float	angle_to_add;
	float	ray_angle;
	int		ray_count;
	float	pi_value;

	pi_value = (float)(atan(1.0) * 4.0);
	game = (t_game *)param;
	handle_movement(game, game->player_data);
	clear_image(game);
	if (game->debug_view)
		draw_square(game->player_data->x, game->player_data->y, 4, game);
	angle_to_add = (ANGLE_OF_VIEW * pi_value / 180) / game->config->s_width;
	ray_angle = game->player_data->angle - (ANGLE_OF_VIEW * pi_value / 180) / 2;
	ray_count = 0;
	while (ray_count < game->config->s_width)
	{
		if (!game->debug_view)
			draw_single_ray_debug(game, game->player_data, ray_angle);
		else
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

int	handle_input_errors(void)
{
	printf("Cub3D: Error\n");
	printf("The correct usage is: ./cub3D [map path]\n");
	return (0);
}

// void	leaks(void)
// {
// 	system("leaks cub3d");
// }
// atexit(leaks);

int	main(int argc, char **argv)
{
	t_game	*game;
	char	*map_file;

	if (argc != 2)
		return (handle_input_errors());
	else if (is_valid_cub_file(argv[1]))
		return (1);
	else
		map_file = ft_strdup(argv[1]);
	game = initialize_game_data(map_file);
	free(map_file);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, ft_player_hook, game);
	mlx_image_to_window(game->mlx, game->player_data->player, 0, 0);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
	return (0);
}
