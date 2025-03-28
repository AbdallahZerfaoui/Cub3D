/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:27:59 by macbook           #+#    #+#             */
/*   Updated: 2025/03/28 23:45:10 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	setup_dda(t_game *game, t_dda *dda, int x)
{
	t_point	*player;
	int		s_width;

	player = game->player_data;
	s_width = game->config->s_width;
	// Calculate ray position and direction
	dda->camera_x = 2.0 * x / (double)s_width - 1.0;
	// x-coordinate in camera space
	dda->ray_dir_x = cos(player->angle) - sin(player->angle) * dda->camera_x;
	dda->ray_dir_y = sin(player->angle) + cos(player->angle) * dda->camera_x;
	// Map position
	dda->map_x = (int)(player->x / game->config->block_size);
	dda->map_y = (int)(player->y / game->config->block_size);
	// Length of ray from current position to next x or y-side
	dda->delta_dist_x = (dda->ray_dir_x == 0) ? 1e30 : fabs(1.0
			/ dda->ray_dir_x);
	dda->delta_dist_y = (dda->ray_dir_y == 0) ? 1e30 : fabs(1.0
			/ dda->ray_dir_y);
	// Calculate step and initial side_dist
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = ((player->x / game->config->block_size) - dda->map_x)
			* dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - (player->x
					/ game->config->block_size)) * dda->delta_dist_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = ((player->y / game->config->block_size) - dda->map_y)
			* dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - (player->y
					/ game->config->block_size)) * dda->delta_dist_y;
	}
	dda->hit = 0;
}

void	perform_dda(t_game *game, t_dda *dda)
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
		if (dda->map_x < 0 || dda->map_y < 0 || dda->map_x >= game->columns
			|| dda->map_y >= game->rows)
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

static uint32_t	convert_color(uint32_t color)
{
	uint8_t	a;
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;

	a = (color >> 24) & 0xFF;
	b = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	r = color & 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

// void	draw_wall_slice(t_game *game, int ray_x_pos, int start_y, int end,t_dda *dda) {
// 	(void)dda;

// 	int				j;
// 	uint32_t		color;
// 	int 			s_height;
// 	int 			tex_x, tex_y;
// 	mlx_texture_t	*texture = game->texture_data->texture;
// 	uint32_t	colord;

// 	// Texture coordinate calculation
// 	tex_x = (int)(dda->wall_x * texture->width);
// 	if (dda->side == 0 && dda->ray_dir_x > 0) {
// 		tex_x = texture->width - tex_x - 1;
			// Flip texture for walls hit from the right
// 	}
// 	if (dda->side == 1 && dda->ray_dir_y < 0) {
// 		tex_x = texture->width - tex_x - 1;
			// Flip texture for walls hit from the top
// 	}

// 	// Texture height and step
// 	// s_height = game->config->s_height;
// 	s_height = texture->height;
// 	dda->step = 1.0 * texture->height / dda->line_height;
// 	dda->tex_pos = (start_y - s_height / 2 + dda->line_height / 2) * dda->step;

// 	j = start_y;
// 	while (j < end) {
// 		// Calculate texture Y coordinate
// 		tex_y = (int)dda->tex_pos & (texture->height - 1);
			// Wrap around the texture height if necessary
// 		dda->tex_pos += dda->step;

// 		// Get the color from the texture at (tex_x, tex_y)
// 		color = ((uint32_t *)texture->pixels)[tex_y * texture->width + tex_x];
// 		// color = ((uint32_t *)texture->pixels)[tex_x * texture->height+ tex_y];
// 		colord = convert_color(color);
// 		// Set the pixel on the screen
// 		mlx_put_pixel(game->player_data->player, ray_x_pos, j, colord);
// 		j++;
// 	}
// }


void	draw_wall_slice(t_game *game, int ray_x, int start_y, int end,
		t_dda *dda)
{
	mlx_texture_t	*tex;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	uint32_t		color;
	uint32_t		colord;

	tex = game->texture_data->texture;
	wall_x = (dda->side == 0) ? game->player_data->y + dda->perp_wall_dist
		* dda->ray_dir_y : game->player_data->x + dda->perp_wall_dist
		* dda->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((dda->side == 0 && dda->ray_dir_x > 0) || (dda->side == 1
			&& dda->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	step = (double)tex->height / dda->line_height;
	tex_pos = (start_y - game->mlx->height / 2 + dda->line_height / 2) * step;
	for (int y = start_y; y < end; y++)
	{
		tex_y = (int)tex_pos % tex->height;
		color = ((uint32_t *)tex->pixels)[tex_y * tex->width + tex_x];
		colord = convert_color(color);
		mlx_put_pixel(game->player_data->player, ray_x, y, colord);
		tex_pos += step;
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
	draw_ceiling_slice(game, ray_count, dda->draw_start);
	// draw_wall_slice(game, ray_count, dda->draw_start, dda->draw_end, dda);
	draw_wall_slice(game, ray_count, dda->draw_start, dda->draw_end, dda);
	draw_floor_slice(game, ray_count, dda->draw_end);
}

void	draw_single_ray(t_game *game, float ray_count)
{
	t_dda	dda;

	setup_dda(game, &dda, ray_count);
	perform_dda(game, &dda);
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
	color = (uint32_t)ft_pixel(128, 128, 128, 255); // grey
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
	while (!check_wall(ray_x, ray_y, game))
	{
		mlx_put_pixel(game->player_data->player, ray_x, ray_y, color);
		ray_x = (cos_angle) + ray_x;
		ray_y = (sin_angle) + ray_y;
	}
}
