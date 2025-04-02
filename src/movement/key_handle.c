/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 05:34:00 by macbook           #+#    #+#             */
/*   Updated: 2025/04/02 22:57:26 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	handle_key_press(struct mlx_key_data keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_W)
		game->player_data->key_up = true;
	if (keydata.key == MLX_KEY_S)
		game->player_data->key_down = true;
	if (keydata.key == MLX_KEY_A)
		game->player_data->key_left = true;
	if (keydata.key == MLX_KEY_D)
		game->player_data->key_right = true;
	if (keydata.key == MLX_KEY_LEFT)
		game->player_data->left_rotate = true;
	if (keydata.key == MLX_KEY_RIGHT)
		game->player_data->right_rotate = true;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(game->mlx);
		free_game(game);
		exit(0);
	}
}

void	handle_key_release(struct mlx_key_data keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_W)
		game->player_data->key_up = false;
	if (keydata.key == MLX_KEY_S)
		game->player_data->key_down = false;
	if (keydata.key == MLX_KEY_A)
		game->player_data->key_left = false;
	if (keydata.key == MLX_KEY_D)
		game->player_data->key_right = false;
	if (keydata.key == MLX_KEY_LEFT)
		game->player_data->left_rotate = false;
	if (keydata.key == MLX_KEY_RIGHT)
		game->player_data->right_rotate = false;
}
