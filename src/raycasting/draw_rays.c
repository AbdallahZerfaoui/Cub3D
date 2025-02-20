/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:27:59 by macbook           #+#    #+#             */
/*   Updated: 2025/02/20 03:41:13 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float ray_x, float ray_y, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = ray_x - x1;
	delta_y = ray_y - y1;
	angle = atan2(delta_y, delta_x) - game->player_data->angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_floor_slice(t_game *game, int i, int start_y)
{
	int	j;
	uint32_t	color;

	j = start_y;
	color = (uint32_t)ft_pixel(255, 255, 0, 255);
	while (j < HEIGHT)
	{
		mlx_put_pixel(game->player_data->player, i, j, color);
		j++;
	}
}

void	draw_ceiling_slice(t_game *game, int i, int ceiling_end)
{
	int	j;
	uint32_t	color;

	j = 0;
	color = (uint32_t)ft_pixel(255, 255, 0, 255);
	while (j < ceiling_end)
	{
		mlx_put_pixel(game->player_data->player, i, j, color);
		j++;
	}
}

void	draw_3d_ray(t_game *game, float ray_x, float ray_y, float ray_count)
{
	float		dist;
	float		height;
	int			start_y;
	int			end;
	uint32_t	color;

	color = (uint32_t)ft_pixel(255, 255, 0, 255);
	(void)color;
	dist = fixed_dist(game->player_data->x, game->player_data->y, ray_x, ray_y,
			game);
	height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	draw_ceiling_slice(game, ray_count, start_y);
	draw_floor_slice(game, ray_count, end);

}

void	draw_single_ray(t_game *game, t_point *player_data, float ray_angle,
		float ray_count)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;

	ray_x = player_data->x;
	ray_y = player_data->y;
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
	while (!check_wall(ray_x, ray_y, game))
	{
		ray_x = cos_angle + ray_x;
		ray_y = sin_angle + ray_y;
	}
	draw_3d_ray(game, ray_x, ray_y, ray_count);
}

void	draw_single_ray_debug(t_game *game, t_point *player_data,
		float ray_angle)
{
	uint32_t	color;
	float		cos_angle;
	float		sin_angle;
	float		ray_x;
	float		ray_y;

	ray_x = player_data->x;
	ray_y = player_data->y;
	color = (uint32_t)ft_pixel(255, 255, 0, 255);
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
	while (!check_wall(ray_x, ray_y, game))
	{
		mlx_put_pixel(game->player_data->player, ray_x, ray_y, color);
		ray_x = cos_angle + ray_x;
		ray_y = sin_angle + ray_y;
	}
}
