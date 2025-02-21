/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:48:32 by macbook           #+#    #+#             */
/*   Updated: 2025/02/21 04:31:23 by macbook          ###   ########.fr       */
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
