/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:57:50 by macbook           #+#    #+#             */
/*   Updated: 2025/03/07 14:43:20 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

bool	neighbor_is_walled(char **map, int i, int j)
{

	int	row_length;
	int	row_count;

	row_length = find_longest_length(map);
	row_count = find_map_row_count(map);
	if ((i == 0 || i == row_count - 1) && (map[i][j] == '0'
		|| is_player_char(map[i][j])))
		return (false);
	else if ((j == 0 || j == row_length - 1) && (map[i][j] == '0'
		|| is_player_char(map[i][j])))
	{
		return (false);
	}
	else if (map[i][j] == '0' || is_player_char(map[i][j]))
	{
		if (map[i][j - 1] == 'x' || map[i][j + 1] == 'x')
			return (false);
		if (map[i - 1][j] == 'x' || map[i + 1][j] == 'x')
			return (false);
		if (map[i - 1][j - 1] == 'x' || map[i - 1][j + 1] == 'x')
			return (false);
		if (map[i + 1][j - 1] == 'x' || map[i + 1][j + 1] == 'x')
			return (false);
	}
	return (true);
}


bool	check_surrounded_by_walls(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!neighbor_is_walled(map, i, j))
			{
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_for_extra_chars(t_game *game, char **map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_char(map[i][j]))
			{
				player_count++;
				game->player_data->direction = map[i][j];
			}
			if (!legit_char(map[i][j]) && map[i][j] != ' ')
				return (printf("Map Contains Invalid Chars\n"), false);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (printf("There should be 1 player on the map\n"), false);
	return (true);
}

char	*create_cleaned_new_row(char **map, int index, int row_length)
{
	int		i;
	bool	in_map;
	char	*new_string;

	i = 0;
	in_map = false;
	new_string = (char *)malloc(sizeof(char) * (row_length + 1));
	if (!new_string)
		return (NULL);
	while (map[index][i])
	{
		if (map[index][i] == '1')
			in_map = !in_map;
		if (legit_char(map[index][i]))
			new_string[i] = map[index][i];
		else
			new_string[i] = 'x';
		i++;
	}
	while (i < row_length)
		new_string[i++] = 'x';
	new_string[i] = '\0';
	return (new_string);
}

char	**create_cleaned_map(char **map)
{
	int		longest_length;
	int		map_row_count;
	char	**new_map;
	int		i;
	int		j;

	j = 0;
	i = 0;
	longest_length = find_longest_length(map);
	map_row_count = find_map_row_count(map);
	while (is_only_whitespace(map[i]))
		i++;
	new_map = (char **)malloc(sizeof(char *) * (map_row_count - i + 1));
	if (!new_map)
		return (NULL);
	while (i < map_row_count)
	{
		new_map[j] = create_cleaned_new_row(map, i, longest_length);
		printf("%s\n", new_map[j]);
		j++;
		i++;
	}
	new_map[j] = NULL;
	return (new_map);
}
