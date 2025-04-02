/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 02:10:05 by azerfaou          #+#    #+#             */
/*   Updated: 2025/04/02 02:37:49 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	setup_dda(t_game *game, t_dda *dda, int x)
{
	setup_ray(game, dda->ray, x);
	state_setup(game, dda->state, dda->ray);
	dda->hit_result->hit = 0;
}

static void	perform_dda_loop(t_dda *dda, t_game *game)
{
	while (dda->hit_result->hit == 0)
	{
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
		if (dda->ray->map_x < 0 || dda->ray->map_y < 0
			|| dda->ray->map_x >= game->columns
			|| dda->ray->map_y >= game->rows)
			dda->hit_result->hit = 1;
		else if (game->map[dda->ray->map_y][dda->ray->map_x] == '1')
			dda->hit_result->hit = 1;
	}
}

static void	calculate_dda_results(t_dda *dda, t_game *game)
{
	if (dda->hit_result->side == 0)
		dda->hit_result->perp_wall_dist = (dda->state->side_dist_x
				- dda->state->delta_dist_x);
	else
		dda->hit_result->perp_wall_dist = (dda->state->side_dist_y
				- dda->state->delta_dist_y);
	dda->draw->line_height = (int)(game->config->s_height
			/ dda->hit_result->perp_wall_dist);
	dda->draw->draw_start = -dda->draw->line_height / 2 + game->config->s_height
		/ 2;
	if (dda->draw->draw_start < 0)
		dda->draw->draw_start = 0;
	dda->draw->draw_end = dda->draw->line_height / 2 + game->config->s_height
		/ 2;
	if (dda->draw->draw_end >= game->config->s_height)
		dda->draw->draw_end = game->config->s_height - 1;
}

void	perform_dda(t_game *game, t_dda *dda)
{
	perform_dda_loop(dda, game);
	calculate_dda_results(dda, game);
}
