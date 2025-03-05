/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:18:04 by macbook           #+#    #+#             */
/*   Updated: 2025/03/05 17:11:04 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	place_elements_on_map(t_game *game, int y, int x)
{
	if (game->map[y][x] == '1' && DEBUG)
		mlx_image_to_window(game->mlx, game->wall, x * BLOCK_SIZE, y
			* BLOCK_SIZE);
	if (game->map[y][x] == '0' && DEBUG)
		mlx_image_to_window(game->mlx, game->background, x * BLOCK_SIZE, y
			* BLOCK_SIZE);
	if (is_player_char(game->map[y][x]))
	{
		if (DEBUG)
			mlx_image_to_window(game->mlx, game->background, x * BLOCK_SIZE, y
				* BLOCK_SIZE);
		game->player_data->x = BLOCK_SIZE * x;
		game->player_data->y = BLOCK_SIZE * y;
	}
}

void	flood_map_items(t_game *game)
{
	int	y;
	int	x;

	game->background = mlx_new_image(game->mlx, BLOCK_SIZE, BLOCK_SIZE);
	game->wall = mlx_new_image(game->mlx, BLOCK_SIZE, BLOCK_SIZE);
	fill_image_pixels(game, game->background,
		(uint32_t)ft_pixel(game->ceiling_color->r, game->ceiling_color->g,
			game->ceiling_color->b, 255));
	fill_image_pixels(game, game->wall, (uint32_t)ft_pixel(game->floor_color->r,
			game->floor_color->g, game->floor_color->b, 255));
	y = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < game->columns)
		{
			place_elements_on_map(game, y, x);
			x++;
		}
		y++;
	}
}

void	init_player(t_game *game, t_point *player_data)
{
	double	pi_value;

	pi_value = atan(1.0) * 4.0;
	player_data->angle_speed = 0.03f;
	player_data->speed = 1;
	if (player_data->direction == 'N')
		player_data->angle = pi_value * 1.5f;
	if (player_data->direction == 'S')
		player_data->angle = pi_value * 0.5f;
	if (player_data->direction == 'W')
		player_data->angle = pi_value;
	if (player_data->direction == 'E')
		player_data->angle = pi_value * 2.0f;
	player_data->key_up = false;
	player_data->key_down = false;
	player_data->key_left = false;
	player_data->key_right = false;
	player_data->left_rotate = false;
	player_data->right_rotate = false;
	player_data->player = mlx_new_image(game->mlx, WIDTH, HEIGHT);
}

void	initialize_textures(t_textures *texture_data)
{
	texture_data->north_path = NULL;
	texture_data->east_path = NULL;
	texture_data->south_path = NULL;
	texture_data->west_path = NULL;
	texture_data->floor_color = NULL;
	texture_data->ceiling_color = NULL;
	texture_data->map_start_index = 0;
}

t_game	*initialize_game_data(void)
{
	t_game	*game;

	game = malloc(1 * sizeof(t_game));
	game->player_data = malloc(sizeof(t_point));
	game->texture_data = malloc(sizeof(t_textures));
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	initialize_textures(game->texture_data);
	game->rows = 0;
	game->columns = 0;
	parse_map(game);
	flood_map_items(game);
	init_player(game, game->player_data);
	return (game);
}
