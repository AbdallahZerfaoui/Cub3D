/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:18:04 by macbook           #+#    #+#             */
/*   Updated: 2025/02/16 21:13:21 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	fill_image_pixels(t_game *game, mlx_image_t *image, uint32_t color)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	(void)game;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			mlx_put_pixel(image, i, j, color);
			j++;
		}
		i++;
	}
}

void	flood_map_items(t_game *game)
{
	int	y;
	int	x;

	game->background = mlx_new_image(game->mlx, BLOCK_SIZE, BLOCK_SIZE);
	game->wall = mlx_new_image(game->mlx, BLOCK_SIZE, BLOCK_SIZE);
	fill_image_pixels(game, game->background, (uint32_t)ft_pixel(25, 25, 25,
			255));
	fill_image_pixels(game, game->wall, (uint32_t)ft_pixel(255, 170, 0, 255));
	y = 0;
	while (y < game->rows)
	{
		// printf("X is: %d\n", x);
		x = 0;
		while (x < game->columns)
		{
			if (game->map[y][x] == '1')
				mlx_image_to_window(game->mlx, game->wall, x * BLOCK_SIZE, y
					* BLOCK_SIZE);
			if (game->map[y][x] == '0')
				mlx_image_to_window(game->mlx, game->background, x * BLOCK_SIZE,
					y * BLOCK_SIZE);
			if (game->map[y][x] == 'N')
			{
				mlx_image_to_window(game->mlx, game->background, x * BLOCK_SIZE,
					y * BLOCK_SIZE);
				game->player_data->x = BLOCK_SIZE * x;
				game->player_data->y = BLOCK_SIZE * y;
			}
			x++;
		}
		y++;
	}
}

void	init_player(t_game *game, t_point *player_data)
{
	player_data->angle_speed = 0.03;
	player_data->speed = 2;
	// player_data->x =  BLOCK_SIZE * 9;
	// player_data->y = BLOCK_SIZE * 2;
	player_data->angle = PI / 2;
	player_data->key_up = false;
	player_data->key_down = false;
	player_data->key_left = false;
	player_data->key_right = false;
	player_data->left_rotate = false;
	player_data->right_rotate = false;
	player_data->player = mlx_new_image(game->mlx, WIDTH, HEIGHT);
}

t_game	*initialize_game_data(void)
{
	t_game *game;

	game = malloc(1 * sizeof(t_game));
	game->player_data = malloc(sizeof(t_point));
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	game->rows = 0;
	game->columns = 0;
	parse_map(game);
	flood_map_items(game);
	init_player(game, game->player_data);
	return (game);
}