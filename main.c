/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:20:16 by macbook           #+#    #+#             */
/*   Updated: 2025/02/21 06:17:27 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_subarrays(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	ft_player_hook(void *param)
{
	t_game	*game;
	double	angle_to_add;
	double	ray_angle;
	int		ray_count;

	game = (t_game *)param;
	handle_movement(game, game->player_data);
	clear_image(game);
	if (DEBUG)
		draw_square(game->player_data->x, game->player_data->y, 4, game);
	angle_to_add = (ANGLE_OF_VIEW * PI / 180) / WIDTH;
	ray_angle = (double)game->player_data->angle - (ANGLE_OF_VIEW * PI / 180)
		/ 2;
	ray_count = 0;
	while (ray_count < WIDTH)
	{
		if (DEBUG)
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

void	leaks(void)
{
	system("leaks cub3D");
}

// printf("North: %s\n", game->texture_data->north_path);
// printf("South: %s\n", game->texture_data->south_path);
// printf("West: %s\n", game->texture_data->west_path);
// printf("East: %s\n", game->texture_data->east_path);
// printf("Floor: %s\n", game->texture_data->floor_color);
// printf("Ceiling: %s\n", game->texture_data->ceiling_color);

int	main(void)
{
	t_game	*game;

	atexit(leaks);
	game = initialize_game_data();
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, ft_player_hook, game);
	mlx_image_to_window(game->mlx, game->player_data->player, 0, 0);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
	return (0);
}
