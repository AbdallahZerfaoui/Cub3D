/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:12:41 by macbook           #+#    #+#             */
/*   Updated: 2025/02/13 20:18:28 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

char	**create_map(char *argv)
{
	char	**map;

	map = initialize_map(argv);
	if (!validate_map(map))
	{
		free_arofar(map, find_rows(map));
		exit(EXIT_FAILURE);
	}
	return (map);
}

void	parse_map(t_game *game)
{
	int i;
	int j;

	i = 0;
	j = 0;
	char map[ROW_COLUMN_COUNT][ROW_COLUMN_COUNT] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '1', '1', '1', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	};
	while (i < ROW_COLUMN_COUNT)
	{
		j = 0;
		while (j < ROW_COLUMN_COUNT)
		{
			game->map[i][j] = map[i][j];
			j++;
		}
		i++;
	}
}