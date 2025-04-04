/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 02:10:58 by azerfaou          #+#    #+#             */
/*   Updated: 2025/04/04 13:30:56 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	draw_floor_slice(t_game *game, int i, int start_y)
{
	int			j;
	uint32_t	color;
	int			s_height;
	int			s_width;

	s_height = game->config->s_height;
	s_width = game->config->s_width;
	if (!game->player_data->player || !game->floor_color)
		return ;
	if (i < 0 || i >= s_width || start_y >= s_height)
		return ;
	if (start_y < 0)
		j = 0;
	else
		j = start_y;
	color = (uint32_t)ft_pixel(game->floor_color->r, game->floor_color->g,
			game->floor_color->b, MAX_RGB_VALUE);
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
			game->ceiling_color->b, MAX_RGB_VALUE);
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
