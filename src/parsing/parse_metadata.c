/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:51:42 by macbook           #+#    #+#             */
/*   Updated: 2025/03/28 19:40:46 by auplisas         ###   ########.fr       */
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
		if (ft_strncmp(map_file[i], "NO ", 3) == 0 && !txtr->north_path)
			txtr->north_path = ft_strtrim(map_file[i] + 3, " \n");
		else if (ft_strncmp(map_file[i], "SO ", 3) == 0 && !txtr->south_path)
			txtr->south_path = ft_strtrim(map_file[i] + 3, " \n");
		else if (ft_strncmp(map_file[i], "WE ", 3) == 0 && !txtr->west_path)
			txtr->west_path = ft_strtrim(map_file[i] + 3, " \n");
		else if (ft_strncmp(map_file[i], "EA ", 3) == 0 && !txtr->east_path)
		{
			txtr->east_path = ft_strtrim(map_file[i] + 3, " \n");
			txtr->texture =  mlx_load_png("./texture/south.png");
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
