/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:58:10 by azerfaou          #+#    #+#             */
/*   Updated: 2025/04/04 13:58:34 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

static t_color	*parse_color(const char *color_str)
{
	char	**rgb;
	t_color	*color;
	long	num;
	int		i;

	rgb = ft_split(color_str, ',');
	if (!rgb)
		(perror("Error\nft_split failed"), exit(1));
	color = malloc(sizeof(t_color));
	if (!color)
		(free_subarrays(rgb), perror("Error\nmalloc failed"), exit(1));
	i = 0;
	while (i++ < 2)
	{
		num = ft_atoi(rgb[i]);
		if (num < 0 || num > 255)
		{
			free_subarrays(rgb);
			free(color);
			(printf("Error\nInvalid color value: %s\n", rgb[i]), exit(1));
		}
		((int *)&color->r)[i] = (int)num;
	}
	free_subarrays(rgb);
	return (color);
}

void	assign_colors(t_game *game)
{
	game->ceiling_color = parse_color(game->texture_data->ceiling_color);
	game->floor_color = parse_color(game->texture_data->floor_color);
}
