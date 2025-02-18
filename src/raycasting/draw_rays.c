/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:27:59 by macbook           #+#    #+#             */
/*   Updated: 2025/02/18 08:03:02 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

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
	color = (uint32_t)ft_pixel(255, 255, 255, 255);
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
	while (!check_wall(ray_x, ray_y, game))
	{
		mlx_put_pixel(game->player_data->player, ray_x, ray_y, color);
		ray_x = cos_angle + ray_x;
		ray_y = sin_angle + ray_y;
	}
}