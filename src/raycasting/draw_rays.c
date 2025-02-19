/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:27:59 by macbook           #+#    #+#             */
/*   Updated: 2025/02/19 04:36:38 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player_data->angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_single_ray(t_game *game, t_point *player_data, float ray_angle,
		float ray_count)
{
	uint32_t	color;
	float		cos_angle;
	float		sin_angle;
	float		ray_x;
	float		ray_y;

	ray_x = player_data->x;
	ray_y = player_data->y;
	(void)ray_angle;
	(void)ray_count;
	color = (uint32_t)ft_pixel(255, 255, 0, 255);
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
	while (!check_wall(ray_x, ray_y, game))
	{
		if(Debug)
			mlx_put_pixel(game->player_data->player, ray_x, ray_y, color);
		ray_x = cos_angle + ray_x;
		ray_y = sin_angle + ray_y;
	}
	// float dist = distance(ray_x = player_data->x, ray_y - player_data->y);
	if(!Debug)
	{
		float dist = fixed_dist(player_data->x, player_data->y, ray_x, ray_y, game);
		float height = (BLOCK_SIZE / dist) * (WIDTH / 2);
		int start_y = (HEIGHT - height) / 2;
		int end = start_y + height;
		while (start_y < end)
		{
			mlx_put_pixel(game->player_data->player, ray_count, start_y, color);
			start_y++;
		}
	}
}