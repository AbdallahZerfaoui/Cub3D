/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:37:15 by macbook           #+#    #+#             */
/*   Updated: 2025/02/19 06:12:51 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

bool	check_wall(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK_SIZE;
	y = py / BLOCK_SIZE;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

void	rotate_player(t_game *game, t_point *player_data)
{
	(void)game;
	if (player_data->left_rotate)
	{
		player_data->angle = player_data->angle - player_data->angle_speed;
	}
	if (player_data->right_rotate)
	{
		player_data->angle = player_data->angle + player_data->angle_speed;
	}
	if (player_data->angle > 2 * PI)
	{
		player_data->angle = 0;
	}
	if (player_data->angle < 0)
	{
		player_data->angle = 2 * PI;
	}
}
void	move_player(t_point *player_data, float *updated_x, float *updated_y)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player_data->angle);
	sin_angle = sin(player_data->angle);
	if (player_data->key_up)
	{
		*updated_x = player_data->x + (cos_angle * player_data->speed);
		*updated_y = player_data->y + (sin_angle * player_data->speed);
	}
	if (player_data->key_down)
	{
		*updated_x = player_data->x - (cos_angle * player_data->speed);
		*updated_y = player_data->y - (sin_angle * player_data->speed);
	}
	if (player_data->key_left)
	{
		*updated_x = player_data->x + (sin_angle * player_data->speed);
		*updated_y = player_data->y - (cos_angle * player_data->speed);
	}
	if (player_data->key_right)
	{
		*updated_x = player_data->x - (sin_angle * player_data->speed);
		*updated_y = player_data->y + (cos_angle * player_data->speed);
	}
}

void	handle_movement(t_game *game, t_point *player_data)
{
	float	updated_x;
	float	updated_y;

	updated_x = player_data->x;
	updated_y = player_data->y;
	rotate_player(game, player_data);
	move_player(player_data, &updated_x, &updated_y);
	if (check_wall(updated_x, updated_y, game))
		return ;
	else
	{
		player_data->x = updated_x;
		player_data->y = updated_y;
	}
}

void	clear_image(t_game *game)
{
	if (!game->player_data->player || !game->player_data->player->pixels)
		return ;
	ft_bzero(game->player_data->player->pixels, game->player_data->player->width
		* game->player_data->player->height * sizeof(int));
}

void	draw_square(float x, float y, int size, t_game *game)
{
	uint32_t	color;
	int			i;

	color = (uint32_t)ft_pixel(255, 255, 255, 255);
	i = 0;
	while (i++ < size)
		mlx_put_pixel(game->player_data->player, x + i, y, color);
	i = 0;
	while (i++ < size)
		mlx_put_pixel(game->player_data->player, x, y + i, color);
	i = 0;
	while (i++ < size)
		mlx_put_pixel(game->player_data->player, x + size, y + i, color);
	i = 0;
	while (i++ < size)
		mlx_put_pixel(game->player_data->player, x + i, y + size, color);
}