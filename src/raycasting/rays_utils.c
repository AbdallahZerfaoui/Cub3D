/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 04:34:57 by macbook           #+#    #+#             */
/*   Updated: 2025/04/02 22:42:56 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

/***
 * fmod function is there just to avoid accumulating
 * errors ex: x=10^-17 instead of 0
 */
int	ft_sign(double x)
{
	return ((x > 0) - (x < 0) + fmod(x, x));
}

bool	check_wall(float px, float py, t_game *game)
{
	int	x;
	int	y;
	int	block_size;

	block_size = game->config->block_size;
	x = px / block_size;
	y = py / block_size;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

int	is_not_valid_color_format(char *color)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (color[i])
	{
		if (color[i] == ',')
			comma_count++;
		else if (!ft_isdigit(color[i]))
			return (1);
		i++;
	}
	if (comma_count != 2)
		return (1);
	return (0);
}

int	check_rgb_values(char **rgb_ceiling, char **rgb_floor)
{
	int	i;
	int	value;

	i = 0;
	while (i < 3)
	{
		value = ft_atoi(rgb_ceiling[i]);
		if (value < 0 || value > 255)
		{
			printf("Error\nInvalid ceiling RGB value: %d\n", value);
			return (1);
		}
		value = ft_atoi(rgb_floor[i]);
		if (value < 0 || value > 255)
		{
			printf("Error\nInvalid floor RGB value: %d\n", value);
			return (1);
		}
		i++;
	}
	return (0);
}
