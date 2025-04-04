/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 02:11:38 by azerfaou          #+#    #+#             */
/*   Updated: 2025/04/04 16:35:21 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	free_dda(t_dda *dda)
{
	if (!dda)
		return ;
	if (dda->ray)
		free(dda->ray);
	if (dda->state)
		free(dda->state);
	if (dda->hit_result)
		free(dda->hit_result);
	if (dda->draw)
		free(dda->draw);
	free(dda);
}

void	draw_single_ray(t_game *game, int ray_count)
{
	t_dda	*dda;

	dda = (t_dda *)ft_calloc(1, sizeof(t_dda));
	if (!dda)
		return ;
	init_dda(dda);
	setup_dda(game, dda, ray_count);
	perform_dda(game, dda);
	draw_wall_slice(game, ray_count, dda);
	free_dda(dda);
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
	color = (uint32_t)ft_pixel(128, 128, 128, MAX_RGB_VALUE);
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
	while (!check_wall(ray_x, ray_y, game))
	{
		mlx_put_pixel(game->player_data->player, ray_x, ray_y, color);
		ray_x = (cos_angle) + ray_x;
		ray_y = (sin_angle) + ray_y;
	}
}
