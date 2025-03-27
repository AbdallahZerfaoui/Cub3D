/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:27:59 by macbook           #+#    #+#             */
/*   Updated: 2025/03/27 22:51:30 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void    setup_dda(t_game *game, t_dda *dda, int x)
{
    t_point *player;
    int     s_width;

    player = game->player_data;
    s_width = game->config->s_width;
    
    // Calculate ray position and direction
    dda->camera_x = 2.0 * x / (double)s_width - 1.0; // x-coordinate in camera space
    dda->ray_dir_x = cos(player->angle) - sin(player->angle) * dda->camera_x;
    dda->ray_dir_y = sin(player->angle) + cos(player->angle) * dda->camera_x;
    
    // Map position
    dda->map_x = (int)(player->x / game->config->block_size);
    dda->map_y = (int)(player->y / game->config->block_size);
    
    // Length of ray from current position to next x or y-side
    dda->delta_dist_x = (dda->ray_dir_x == 0) ? 1e30 : fabs(1.0 / dda->ray_dir_x);
    dda->delta_dist_y = (dda->ray_dir_y == 0) ? 1e30 : fabs(1.0 / dda->ray_dir_y);
    
    // Calculate step and initial side_dist
    if (dda->ray_dir_x < 0)
    {
        dda->step_x = -1;
        dda->side_dist_x = ((player->x / game->config->block_size) - dda->map_x) * dda->delta_dist_x;
    }
    else
    {
        dda->step_x = 1;
        dda->side_dist_x = (dda->map_x + 1.0 - (player->x / game->config->block_size)) * dda->delta_dist_x;
    }
    if (dda->ray_dir_y < 0)
    {
        dda->step_y = -1;
        dda->side_dist_y = ((player->y / game->config->block_size) - dda->map_y) * dda->delta_dist_y;
    }
    else
    {
        dda->step_y = 1;
        dda->side_dist_y = (dda->map_y + 1.0 - (player->y / game->config->block_size)) * dda->delta_dist_y;
    }
    dda->hit = 0;
}

void    perform_dda(t_game *game, t_dda *dda)
{
    // Perform DDA
    while (dda->hit == 0)
    {
        // Jump to next map square, either in x-direction, or in y-direction
        if (dda->side_dist_x < dda->side_dist_y)
        {
            dda->side_dist_x += dda->delta_dist_x;
            dda->map_x += dda->step_x;
            dda->side = 0;
        }
        else
        {
            dda->side_dist_y += dda->delta_dist_y;
            dda->map_y += dda->step_y;
            dda->side = 1;
        }
        
        // Check if ray has hit a wall
        if (dda->map_x < 0 || dda->map_y < 0 || dda->map_x >= game->columns || dda->map_y >= game->rows)
            dda->hit = 1;
        else if (game->map[dda->map_y][dda->map_x] == '1')
            dda->hit = 1;
    }
    
    // Calculate distance projected on camera direction
    if (dda->side == 0)
        dda->perp_wall_dist = (dda->side_dist_x - dda->delta_dist_x);
    else
        dda->perp_wall_dist = (dda->side_dist_y - dda->delta_dist_y);
    
    // Calculate height of line to draw on screen
    dda->line_height = (int)(game->config->s_height / dda->perp_wall_dist);
    
    // Calculate lowest and highest pixel to fill in current stripe
    dda->draw_start = -dda->line_height / 2 + game->config->s_height / 2;
    if (dda->draw_start < 0)
        dda->draw_start = 0;
    dda->draw_end = dda->line_height / 2 + game->config->s_height / 2;
    if (dda->draw_end >= game->config->s_height)
        dda->draw_end = game->config->s_height - 1;
}

void	draw_floor_slice(t_game *game, int i, int start_y)
{
	int			j;
	uint32_t	color;
	int			s_height;

	s_height = game->config->s_height;
	j = start_y;
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

void	draw_wall_slice(t_game *game, int i, int start_y, int end)
{
	int			j;
	uint32_t	color;
	int s_height;
	
	s_height = game->config->s_height;
	j = start_y;
	color = (uint32_t)ft_pixel(51, 51, 51, 255);
	while (j < end)
	{
		mlx_put_pixel(game->player_data->player, i, j, color);
		j++;
	}
}

void	draw_3d_ray(t_game *game, t_dda *dda, int ray_count)
{
	// double	dist;
	// double	height;//TODO change the name
	// int		start_y;
	// int		end;
	// int		block_size;
	// int		s_height;

	// s_height = game->config->s_height;
	// block_size = game->config->block_size;
	// dist = fixed_dist(ray_x, ray_y, game);
	// height = (block_size * s_height) / (dist * tan(FOV / 2.0));
	// if (height > s_height)
	// 	height = s_height;
	// start_y = (s_height - height) / 2;
	// end = start_y + height;
	draw_ceiling_slice(game, ray_count, dda->draw_start);
	// draw_wall_slice(game, ray_count, dda->draw_start);
	draw_floor_slice(game, ray_count, dda->draw_end);
}

void	draw_single_ray(t_game *game, t_point *player_data, float ray_angle,
		float ray_count)
{
	(void)ray_angle;
	(void)ray_count;
	(void)player_data;
	t_dda dda;
	setup_dda(game, &dda, ray_count);
	perform_dda(game, &dda);
	// double	cos_angle;
	// double	sin_angle;
	// double	ray_x;
	// double	ray_y;

	// ray_x = player_data->x;
	// ray_y = player_data->y;
	// cos_angle = cos(ray_angle);
	// sin_angle = sin(ray_angle);
	// while (!check_wall(ray_x, ray_y, game))
	// {
	// 	ray_x = (cos_angle * 0.1) + ray_x;
	// 	ray_y = (sin_angle * 0.1) + ray_y;
	// }
	draw_3d_ray(game, &dda, ray_count);
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
