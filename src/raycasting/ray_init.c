/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 02:09:02 by azerfaou          #+#    #+#             */
/*   Updated: 2025/04/04 13:28:55 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	setup_ray(t_game *game, t_dda_ray *ray, int x)
{
	t_point	*player;
	int		s_width;

	player = game->player_data;
	s_width = game->config->s_width;
	ray->camera_x = 2.0 * x / (double)s_width - 1.0;
	ray->ray_dir_x = cos(player->angle) - sin(player->angle) * ray->camera_x;
	ray->ray_dir_y = sin(player->angle) + cos(player->angle) * ray->camera_x;
	ray->map_x = (int)(player->x / game->config->block_size);
	ray->map_y = (int)(player->y / game->config->block_size);
}

void	init_delta_dists(t_dda_state *state, t_dda_ray *ray)
{
	if (fabs(ray->ray_dir_x) < TOLERANCE)
		state->delta_dist_x = MAX_RAY_DISTANCE;
	else
		state->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (fabs(ray->ray_dir_y) < TOLERANCE)
		state->delta_dist_y = MAX_RAY_DISTANCE;
	else
		state->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

void	set_side_dist_x(t_dda_state *state, t_dda_ray *ray, t_game *game)
{
	t_point	*player;

	player = game->player_data;
	if (ray->ray_dir_x < 0)
	{
		state->side_dist_x = ((player->x / game->config->block_size)
				- ray->map_x) * state->delta_dist_x;
	}
	else
	{
		state->side_dist_x = (ray->map_x + 1.0 - (player->x
					/ game->config->block_size)) * state->delta_dist_x;
	}
}

void	set_side_dist_y(t_dda_state *state, t_dda_ray *ray, t_game *game)
{
	t_point	*player;

	player = game->player_data;
	if (ray->ray_dir_y < 0)
	{
		state->side_dist_y = ((player->y / game->config->block_size)
				- ray->map_y) * state->delta_dist_y;
	}
	else
	{
		state->side_dist_y = (ray->map_y + 1.0 - (player->y
					/ game->config->block_size)) * state->delta_dist_y;
	}
}

void	state_setup(t_game *game, t_dda_state *state, t_dda_ray *ray)
{
	init_delta_dists(state, ray);
	state->step_x = ft_sign(ray->ray_dir_x);
	state->step_y = ft_sign(ray->ray_dir_y);
	set_side_dist_x(state, ray, game);
	set_side_dist_y(state, ray, game);
}
