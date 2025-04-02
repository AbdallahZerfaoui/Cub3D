/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:38:10 by auplisas          #+#    #+#             */
/*   Updated: 2025/04/02 19:38:39 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

bool	is_only_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_all_textures_set(t_textures *texture_data)
{
	int	i;

	i = 0;
	if (texture_data->north_path)
		i++;
	if (texture_data->south_path)
		i++;
	if (texture_data->east_path)
		i++;
	if (texture_data->west_path)
		i++;
	if (texture_data->ceiling_color)
		i++;
	if (texture_data->floor_color)
		i++;
	if (i < 6)
		return (false);
	else
		return (true);
}

int	set_textures(t_textures *txtr, char **map_file)
{
	int	i;

	i = 0;
	while (!check_all_textures_set(txtr))
	{
		printf("EA path: %s\n", map_file[i]);
		if (ft_strncmp(map_file[i], "NO ", 3) == 0 && !txtr->north_path)
		{
			txtr->north_path = ft_strtrim(map_file[i] + 3, " \n");
			txtr->north_texture = mlx_load_png(txtr->north_path);
			if (!txtr->north_texture)
				return (1);
		}
		else if (ft_strncmp(map_file[i], "SO ", 3) == 0 && !txtr->south_path)
		{
			txtr->south_path = ft_strtrim(map_file[i] + 3, " \n");
			txtr->south_texture = mlx_load_png(txtr->south_path);
			if (!txtr->south_texture)
				return (1);
		}
		else if (ft_strncmp(map_file[i], "WE ", 3) == 0 && !txtr->west_path)
		{
			txtr->west_path = ft_strtrim(map_file[i] + 3, " \n");
			txtr->west_texture = mlx_load_png(txtr->west_path);
			if (!txtr->west_texture)
				return (1);
		}
		else if (ft_strncmp(map_file[i], "EA ", 3) == 0 && !txtr->east_path)
		{
			txtr->east_path = ft_strtrim(map_file[i] + 3, " \n");
			txtr->east_texture = mlx_load_png(txtr->east_path);
			if (!txtr->east_texture)
				return (1);
		}
		else if (ft_strncmp(map_file[i], "F ", 2) == 0 && !txtr->floor_color)
			txtr->floor_color = ft_strtrim(map_file[i] + 2, " \n");
		else if (ft_strncmp(map_file[i], "C ", 2) == 0 && !txtr->ceiling_color)
			txtr->ceiling_color = ft_strtrim(map_file[i] + 2, " \n");
		else if (is_only_whitespace(map_file[i]))
			;
		else
			return (1);
		i++;
	}
	txtr->map_start_index = i;
	return (0);
}
