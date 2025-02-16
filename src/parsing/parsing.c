/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:12:41 by macbook           #+#    #+#             */
/*   Updated: 2025/02/17 01:22:55 by macbook          ###   ########.fr       */
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
// char    **initialize_map()
// {
//     int     fd, i, len, max_len = 0;
//     char    *line;
//     char    *array;
//     char    **map;

//     fd = open("./map1.ber", O_RDONLY);
//     if (fd < 0)
//         return (write(1, "Error\nFile N/A\n", 15), exit(EXIT_FAILURE), NULL);
//     array = ft_strdup("");
//     line = get_next_line(fd);
//     while (line)
//     {
//         len = strlen(line);
//         if (len > max_len)
//             max_len = len;
//         array = join_str(array, line);
//         free(line);
//         line = get_next_line(fd);
//     }
//     close(fd);

//     map = ft_split(array, '\n');
//     free(array);

//     for (i = 0; map[i]; i++)
//     {
//         len = strlen(map[i]);
//         char *new_line = malloc(max_len + 1);
//         memset(new_line, 'x', max_len);
//         strcpy(new_line + (max_len - len), map[i]);
//         new_line[max_len] = '\0';
//         free(map[i]);
//         map[i] = new_line;
//     }
//     return (map);
// }

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

bool	legit_char(char c)
{
	if (c == '1' || c == '0')
		return (true);
	if (c == 'N')
		return (true);
	return (false);
}
char	*create_cleaned_new_row(char **map, int index, int row_length)
{
	int		i;
	char	*new_string;

	i = 0;
	new_string = (char *)malloc(sizeof(char) * (row_length + 1));
	if (!new_string)
		return (NULL);
	while (map[index][i])
	{
		if (legit_char(map[index][i]))
			new_string[i] = map[index][i];
		else
			new_string[i] = 'x';
		i++;
	}
	while (i < row_length)
	{
		new_string[i] = 'x';
		i++;
	}
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
void	parse_map(t_game *game)
{
	// int i;
	// int j;

	// i = 0;
	// j = 0;
	char **map;
	char **cleaned_map;
	map = create_map();
	cleaned_map = create_cleaned_map(map);
	print_subarrays(cleaned_map);
	count_rows_columns(game, cleaned_map);
	// printf("Columns are: %d\n", game->columns);
	// printf("Rows are: %d\n", game->rows);
	game->map = cleaned_map;
	// char map[ROW_COLUMN_COUNT][ROW_COLUMN_COUNT] = {
	// 	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	// 	{'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	// 	{'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	// 	{'1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '1'},
	// 	{'1', '0', '0', '0', '1', '1', '1', '0', '0', '0', '0', '1'},
	// 	{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
	// 	{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
	// 	{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
	// 	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	// 	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	// 	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	// 	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	// };
	// while (i < ROW_COLUMN_COUNT)
	// {
	// 	j = 0;
	// 	while (j < ROW_COLUMN_COUNT)
	// 	{
	// 		game->map[i][j] = map[i][j];
	// 		j++;
	// 	}
	// 	i++;
	// }
}