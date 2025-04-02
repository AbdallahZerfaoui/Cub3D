/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 04:12:31 by macbook           #+#    #+#             */
/*   Updated: 2025/04/02 21:41:26 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	free_subarrays(char **subarrays)
{
	int	i;

	i = 0;
	if (!subarrays)
		return ;
	while (subarrays[i])
	{
		free(subarrays[i]);
		i++;
	}
	free(subarrays);
}

void	free_texture_data(t_textures *texture_data)
{
	if (texture_data)
	{
		if (texture_data->north_path)
			free(texture_data->north_path);
		if (texture_data->south_path)
			free(texture_data->south_path);
		if (texture_data->west_path)
			free(texture_data->west_path);
		if (texture_data->east_path)
			free(texture_data->east_path);
		if (texture_data->floor_color)
			free(texture_data->floor_color);
		if (texture_data->ceiling_color)
			free(texture_data->ceiling_color);
	}
}

void	free_textures(t_textures *texture_data)
{
	if (texture_data)
	{
		if (texture_data->north_texture)
		{
			mlx_delete_texture(texture_data->north_texture);
		}
		if (texture_data->south_texture)
		{
			mlx_delete_texture(texture_data->south_texture);
		}
		if (texture_data->west_texture)
		{
			mlx_delete_texture(texture_data->west_texture);
		}
		if (texture_data->east_texture)
		{
			mlx_delete_texture(texture_data->east_texture);
		}
	}
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_subarrays(game->map);
	if (game->map_file)
		free(game->map_file);
	if (game->player_data)
		free(game->player_data);
	if (game->texture_data)
	{
		free_texture_data(game->texture_data);
		free_textures(game->texture_data);
		free(game->texture_data);
	}
	if (game->config)
		free(game->config);
	if (game->ceiling_color)
		free(game->ceiling_color);
	if (game->floor_color)
		free(game->floor_color);
	free(game);
}
