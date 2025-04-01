/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:12:41 by macbook           #+#    #+#             */
/*   Updated: 2025/04/01 22:41:24 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

char	**create_map(char *map_file)
{
	int		fd;
	char	*line;
	char	*array;
	char	**map;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (write(1, "Error\nFile N/A\n", 15), exit(EXIT_FAILURE), NULL);
	array = ft_strdup("");
	line = get_next_line(fd);
	while (line != NULL)
	{
		array = join_str(array, line);
		if (line != NULL)
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map = ft_split(array, '\n');
	free(array);
	return (map);
}

void	count_rows_columns(t_game *game, char **map)
{
	int	rows;
	int	columns;

	rows = 0;
	columns = 0;
	while (map[rows])
	{
		columns = 0;
		while (map[rows][columns])
			columns++;
		rows++;
	}
	game->rows = rows;
	game->columns = columns;
}

char	**create_only_map(t_textures *texture_data, char **map_file)
{
	int		start_index;
	char	**new_map;
	int		i;
	int		j;
	int		map_length;

	i = 0;
	j = 0;
	map_length = 0;
	start_index = texture_data->map_start_index;
	while (map_file[map_length] != NULL)
		map_length++;
	new_map = (char **)malloc((map_length - start_index + 1) * sizeof(char *));
	if (new_map == NULL)
		return (NULL);
	i = start_index;
	while (i < map_length)
		new_map[j++] = ft_strdup(map_file[i++]);
	new_map[j] = NULL;
	return (new_map);
}

void	assign_colors(t_game *game)
{
	char	**rgb_ceiling;
	char	**rgb_floor;

	game->ceiling_color = malloc(sizeof(t_color));
	game->floor_color = malloc(sizeof(t_color));
	rgb_ceiling = ft_split(game->texture_data->ceiling_color, ',');
	rgb_floor = ft_split(game->texture_data->floor_color, ',');
	game->ceiling_color->r = ft_atoi(rgb_ceiling[0]);
	game->ceiling_color->g = ft_atoi(rgb_ceiling[1]);
	game->ceiling_color->b = ft_atoi(rgb_ceiling[2]);
	game->floor_color->r = ft_atoi(rgb_floor[0]);
	game->floor_color->g = ft_atoi(rgb_floor[1]);
	game->floor_color->b = ft_atoi(rgb_floor[2]);
	free_subarrays(rgb_ceiling);
	free_subarrays(rgb_floor);
}

void	parse_map(t_game *game)
{
	char	**parsed_map_file;
	char	**map;
	char	**cleaned_map;

	parsed_map_file = create_map(game->map_file);
	if (set_textures(game->texture_data, parsed_map_file))
	{
		printf("Wrong Char or File Found\n");
		exit(1);
	}
	map = create_only_map(game->texture_data, parsed_map_file);
	cleaned_map = create_cleaned_map(map);
	if (!check_for_extra_chars(game, map))
		exit(1);
	if (!check_surrounded_by_walls(cleaned_map))
	{
		printf("Error: Map not surrounded by walls\n");
		exit(1);
	}
	count_rows_columns(game, cleaned_map);
	assign_colors(game);
	free_subarrays(parsed_map_file);
	free_subarrays(map);
	game->map = cleaned_map;
}
