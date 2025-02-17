/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:12:41 by macbook           #+#    #+#             */
/*   Updated: 2025/02/17 06:00:11 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

char	*join_str(char *buffer, char *tmp)
{
	char	*str;

	str = ft_strjoin(buffer, tmp);
	free(buffer);
	return (str);
}

void	print_subarrays(char **map)
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
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

char	**create_map(void)
{
	int		fd;
	char	*line;
	char	*array;
	char	**map;

	fd = open("./map.ber", O_RDONLY);
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
	// print_subarrays(map);
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
		{
			columns++;
		}
		rows++;
	}
	game->rows = rows;
	game->columns = columns;
}

size_t	find_longest_length(char **map)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > len)
			len = ft_strlen(map[i]);
		i++;
	}
	return (len);
}

int	find_map_row_count(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

bool	is_player_char(char c)
{
	if (c == 'N' || c == 'S')
		return (true);
	if (c == 'E' || c == 'W')
		return (true);
	return (false);
}

bool	legit_char(char c)
{
	if (c == '1' || c == '0')
		return (true);
	if (is_player_char(c))
		return (true);
	return (false);
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
		else if (in_map)
			new_string[i] = '0';
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

	i = 0;
	longest_length = find_longest_length(map);
	map_row_count = find_map_row_count(map);
	new_map = (char **)malloc(sizeof(char *) * (longest_length + 1));
	if (!new_map)
		return (NULL);
	while (i < map_row_count)
	{
		new_map[i] = create_cleaned_new_row(map, i, longest_length);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

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
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
bool	check_for_extra_chars(char **map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	j = 0;
	player_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_char(map[i][j]))
				player_count++;
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

void	parse_map(t_game *game)
{
	char **map;
	char **cleaned_map;
	map = create_map();
	cleaned_map = create_cleaned_map(map);
	print_subarrays(cleaned_map);
	if (!check_for_extra_chars(map))
	{
		exit(1);
	}
	if (!check_surrounded_by_walls(cleaned_map))
	{
		printf("Error: Map not surrounded by walls\n");
		exit(1);
	}
	count_rows_columns(game, cleaned_map);
	game->map = cleaned_map;
}