/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:27:59 by macbook           #+#    #+#             */
/*   Updated: 2025/03/05 22:53:23 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	draw_floor_slice(t_game *game, int i, int start_y)
{
	int			j;
	uint32_t	color;

	j = start_y;
	color = (uint32_t)ft_pixel(game->floor_color->r, game->floor_color->g,
			game->floor_color->b, 255);
	while (j < HEIGHT)
	{
		mlx_put_pixel(game->player_data->player, i, j, color);
		j++;
	}
}

void	draw_ceiling_slice(t_game *game, int i, int ceiling_end)
{
	int			j;
	uint32_t	color;

	j = 0;
	color = (uint32_t)ft_pixel(game->ceiling_color->r, game->ceiling_color->g,
			game->ceiling_color->b, 255);
	while (j < ceiling_end)
	{
		mlx_put_pixel(game->player_data->player, i, j, color);
		j++;
	}
}

void	draw_wall_slice(t_game *game, int i, int start_y, int end)
{
	int			j;
	uint32_t	color;

	j = start_y;
	color = (uint32_t)ft_pixel(51, 51, 51, 255);
	while (j < end)
	{
		mlx_put_pixel(game->player_data->player, i, j, color);
		j++;
	}
}

void	draw_3d_ray(t_game *game, double ray_x, double ray_y, float ray_count)
{
	double	dist;
	double	height;
	int		start_y;
	int		end;

	dist = fixed_dist(ray_x, ray_y, game);
	height = (BLOCK_SIZE * HEIGHT) / (dist * tan(FOV / 2.0));
	if (height > HEIGHT)
		height = HEIGHT;
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	draw_ceiling_slice(game, ray_count, start_y);
	draw_wall_slice(game, ray_count, start_y, end);
	draw_floor_slice(game, ray_count, end);
}

void	draw_single_ray(t_game *game, t_point *player_data, float ray_angle,
		float ray_count)
{
	double	cos_angle;
	double	sin_angle;
	double	ray_x;
	double	ray_y;

	ray_x = player_data->x;
	ray_y = player_data->y;
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
	while (!check_wall(ray_x, ray_y, game))
	{
		ray_x = (cos_angle * 0.1) + ray_x;
		ray_y = (sin_angle * 0.1) + ray_y;
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
	color = (uint32_t)ft_pixel(128, 128, 128, 255); //grey
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
	while (!check_wall(ray_x, ray_y, game))
	{
		mlx_put_pixel(game->player_data->player, ray_x, ray_y, color);
		ray_x = (cos_angle) + ray_x;
		ray_y = (sin_angle) + ray_y;
	}
}
