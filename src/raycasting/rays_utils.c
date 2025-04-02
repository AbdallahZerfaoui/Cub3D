/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 04:34:57 by macbook           #+#    #+#             */
/*   Updated: 2025/04/02 20:33:40 by auplisas         ###   ########.fr       */
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
