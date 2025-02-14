/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:12:41 by macbook           #+#    #+#             */
/*   Updated: 2025/02/14 01:03:08 by auplisas         ###   ########.fr       */
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

char	**initialize_map()
{
	int		fd;
	char	*line;
	char	*array;
	char	**map;

	fd = open("./map2.ber", O_RDONLY);
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
	// if (check_for_double_nl(array))
	// 	return (write(1,
	// 			"Error\nYour map contains multiple New Lines in a Row\n", 53),
	// 		free(array), exit(1), NULL);
	map = ft_split(array, '\n');
	free(array);
	return (map);
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

char	**create_map()
{
	char	**map;

	map = initialize_map();
	// print_subarrays(map);
	// if (!validate_map(map))
	// {
	// 	free_arofar(map, find_rows(map));
	// 	exit(EXIT_FAILURE);
	// }
	return (map);
}

void count_rows_columns(t_game *game,char **map)
{
	int rows;
	int columns;

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

void	parse_map(t_game *game)
{
	int i;
	int j;

	i = 0;
	j = 0;
	char **map;
	map = create_map();
	print_subarrays(map);
	count_rows_columns(game, map);
	printf("Columns are: %d\n", game->columns);
	printf("Rows are: %d\n", game->rows);
	game->map = map;
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