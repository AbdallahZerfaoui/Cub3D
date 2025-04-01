/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/01 23:26:04 by auplisas         ###   ########.fr       */
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
	double	tolerance;

	tolerance = 1e-6;
	if (fabs(ray->ray_dir_x) < tolerance)
		state->delta_dist_x = MAX_RAY_DISTANCE;
	else
		state->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (fabs(ray->ray_dir_y) < tolerance)
		state->delta_dist_y = MAX_RAY_DISTANCE;
	else
		state->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}
void	state_setup(t_game *game, t_dda_state *state, t_dda_ray *ray)
{
	t_point	*player;
	int		s_width;

	player = game->player_data;
	s_width = game->config->s_width;
	(void)s_width;
	init_delta_dists(state, ray);
	state->step_x = ft_sign(ray->ray_dir_x);
	state->step_y = ft_sign(ray->ray_dir_y);
	// Calculate step and initial side_dist
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

void	setup_dda(t_game *game, t_dda *dda, int x)
{
	t_point	*player;
	int		s_width;

	(void)player;
	(void)s_width;
	player = game->player_data;
	s_width = game->config->s_width;
	setup_ray(game, dda->ray, x);
	// Length of ray from current position to next x or y-side
	state_setup(game, dda->state, dda->ray);
	dda->hit_result->hit = 0;
}

void	perform_dda(t_game *game, t_dda *dda)
{
	while (dda->hit_result->hit == 0)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (dda->state->side_dist_x < dda->state->side_dist_y)
		{
			dda->state->side_dist_x += dda->state->delta_dist_x;
			dda->ray->map_x += dda->state->step_x;
			dda->hit_result->side = 0;
		}
		else
		{
			dda->state->side_dist_y += dda->state->delta_dist_y;
			dda->ray->map_y += dda->state->step_y;
			dda->hit_result->side = 1;
		}
		// Check if ray has hit a wall
		if (dda->ray->map_x < 0 || dda->ray->map_y < 0
			|| dda->ray->map_x >= game->columns
			|| dda->ray->map_y >= game->rows)
			dda->hit_result->hit = 1;
		else if (game->map[dda->ray->map_y][dda->ray->map_x] == '1')
			dda->hit_result->hit = 1;
	}
	// Calculate distance projected on camera direction
	if (dda->hit_result->side == 0)
		dda->hit_result->perp_wall_dist = (dda->state->side_dist_x
				- dda->state->delta_dist_x);
	else
		dda->hit_result->perp_wall_dist = (dda->state->side_dist_y
				- dda->state->delta_dist_y);
	// Calculate height of line to draw on screen
	dda->draw->line_height = (int)(game->config->s_height
			/ dda->hit_result->perp_wall_dist);
	// Calculate lowest and highest pixel to fill in current stripe
	dda->draw->draw_start = -dda->draw->line_height / 2 + game->config->s_height
		/ 2;
	if (dda->draw->draw_start < 0)
		dda->draw->draw_start = 0;
	dda->draw->draw_end = dda->draw->line_height / 2 + game->config->s_height
		/ 2;
	if (dda->draw->draw_end >= game->config->s_height)
		dda->draw->draw_end = game->config->s_height - 1;
}

void	draw_floor_slice(t_game *game, int i, int start_y)
{
	int			j;
	uint32_t	color;
	int			s_height;
	int			s_width;

	s_height = game->config->s_height;
	s_width = game->config->s_width;

	if (!game->player_data->player || !game->floor_color)
		return;

	if (i < 0 || i >= s_width || start_y >= s_height)
		return;

	j = (start_y < 0) ? 0 : start_y;
	color = (uint32_t)ft_pixel(game->floor_color->r, game->floor_color->g,
			game->floor_color->b, 255);
	while (j < s_height)
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

void	draw_3d_ray(t_game *game, t_dda *dda, int ray_count)
{
	draw_ceiling_slice(game, ray_count, dda->draw->draw_start);
	draw_wall_slice(game, ray_count, dda);
	draw_floor_slice(game, ray_count, dda->draw->draw_end);
}

void	draw_single_ray(t_game *game, t_point *player_data, float ray_angle,
		float ray_count)
{
	t_dda	*dda;

	dda = (t_dda *)ft_calloc(1, sizeof(t_dda));
	init_dda(dda);
	(void)ray_angle;
	(void)ray_count;
	(void)player_data;
	setup_dda(game, dda, ray_count);
	perform_dda(game, dda);
	draw_3d_ray(game, dda, ray_count);
	free(dda);
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
	color = (uint32_t)ft_pixel(128, 128, 128, 255);
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
	while (!check_wall(ray_x, ray_y, game))
	{
		mlx_put_pixel(game->player_data->player, ray_x, ray_y, color);
		ray_x = (cos_angle) + ray_x;
		ray_y = (sin_angle) + ray_y;
	}
}
