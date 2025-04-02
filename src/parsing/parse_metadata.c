/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:38:10 by auplisas          #+#    #+#             */
/*   Updated: 2025/04/02 19:46:08 by auplisas         ###   ########.fr       */
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

int	load_texture(char *line, char **path, mlx_texture_t **texture)
{
	*path = ft_strtrim(line, " \n");
	*texture = mlx_load_png(*path);
	return (*texture == NULL);
}

int	process_texture_line(t_textures *txtr, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !txtr->north_path)
		return (load_texture(line + 3, &txtr->north_path,
				&txtr->north_texture));
	else if (ft_strncmp(line, "SO ", 3) == 0 && !txtr->south_path)
		return (load_texture(line + 3, &txtr->south_path,
				&txtr->south_texture));
	else if (ft_strncmp(line, "WE ", 3) == 0 && !txtr->west_path)
		return (load_texture(line + 3, &txtr->west_path, &txtr->west_texture));
	else if (ft_strncmp(line, "EA ", 3) == 0 && !txtr->east_path)
		return (load_texture(line + 3, &txtr->east_path, &txtr->east_texture));
	else if (ft_strncmp(line, "F ", 2) == 0 && !txtr->floor_color)
		txtr->floor_color = ft_strtrim(line + 2, " \n");
	else if (ft_strncmp(line, "C ", 2) == 0 && !txtr->ceiling_color)
		txtr->ceiling_color = ft_strtrim(line + 2, " \n");
	else if (!is_only_whitespace(line))
		return (1);
	return (0);
}

int	set_textures(t_textures *txtr, char **map_file)
{
	int	i;

	i = 0;
	while (!check_all_textures_set(txtr))
	{
		if (process_texture_line(txtr, map_file[i]))
			return (1);
		i++;
	}
	txtr->map_start_index = i;
	return (0);
}
