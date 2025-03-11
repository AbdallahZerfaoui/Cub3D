/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:56:11 by azerfaou          #+#    #+#             */
/*   Updated: 2025/03/11 16:59:42 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # define WIDTH 2560
// # define HEIGHT 1440
# define TMP_VALUE 666
# define ROW_COLUMN_COUNT 12
// # define BLOCK_SIZE 43 // Because WIDTH / ROW_COLUMN_COUNT (516 / 12)
// # define PI 3.14159265359
// # define PI (acos(1.0) / 4.0)
# define ANGLE_OF_VIEW 60
// # define DEBUG 1
// # define BLOCK_SIZE 24
// # define FOV 1.0472f
# define FOV (4 * atan(1.0) / 3.0)

// Includes -- BEGIN
# include "../MLX42/include/MLX42/MLX42.h"
# include "../lib/lib.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
// # include <CoreGraphics/CoreGraphics.h>

// Includes -- END

// extern const double	PI;
// const double g_PI = acos(1.0) / 4.0;

typedef struct s_point
{
	char		direction;
	int			speed;
	float		angle_speed;
	bool		key_up;
	bool		key_right;
	bool		key_left;
	bool		key_down;
	bool		left_rotate;
	bool		right_rotate;
	float		angle;
	float		x;
	float		y;
	mlx_image_t	*player;
}				t_point;

typedef struct s_textures
{
	int			map_start_index;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	char		*floor_color;
	char		*ceiling_color;
}				t_textures;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;

}				t_color;

typedef struct s_config
{
	int	s_width;
	int	s_height;
	int	block_size;
}				t_config;

typedef struct s_game
{
	mlx_t		*mlx;
	int			columns;
	int			rows;
	int			debug_view; //1: 2D, 0: 3D
	// char		map[12][12];
	t_config	*config;
	char		*map_file;
	char		**map;
	int			block_size;
	t_point		*player_data;
	t_textures	*texture_data;
	t_color		*ceiling_color;
	t_color		*floor_color;
	mlx_image_t	*background;
	mlx_image_t	*wall;
}				t_game;

// FNC --BEGIN
void			printHello(void);
bool			check_wall(float px, float py, t_game *game);
// PARSING
// parse_utils.c
bool			legit_char(char c);
bool			is_player_char(char c);
int				find_map_row_count(char **map);
size_t			find_longest_length(char **map);
char			*join_str(char *buffer, char *tmp);
// parse_metadata.c
bool			is_only_whitespace(char *str);
int				set_textures(t_textures *txtr, char **map_file);
// parse_map.c
char			**create_cleaned_map(char **map);
char			*create_cleaned_new_row(char **map, int index, int row_length);
bool			check_for_extra_chars(t_game *game, char **map);
bool			check_surrounded_by_walls(char **map);
bool			neighbor_is_walled(char **map, int i, int j);
// parsing.c
void			parse_map(t_game *game);
// INITIALIZE
// initialize.c
t_game			*initialize_game_data(char *map_file);
void			flood_map_items(t_game *game);
void			init_player(t_game *game, t_point *player_data);
// initialize_utils.c
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void			fill_image_pixels(t_game *game, mlx_image_t *image,
					uint32_t color);
// RAYCASTING
// draw_rays.c
void			draw_single_ray(t_game *game, t_point *player_data,
					float ray_angle, float ray_count);
void			draw_single_ray_debug(t_game *game, t_point *player_data,
					float ray_angle);
// rays_utils.c
bool			check_wall(float px, float py, t_game *game);
double			fixed_dist(double ray_x, double ray_y, t_game *game);
// MOVEMENT
// key_handle.c
void			handle_key_press(struct mlx_key_data keydata, t_game *game);
void			handle_key_release(struct mlx_key_data keydata, t_game *game);
// move.c
void			handle_movement(t_game *game, t_point *player_data);
void			clear_image(t_game *game);
void			draw_square(float x, float y, int size, t_game *game);
// FREE
// free.c
void			free_subarrays(char **subarrays);
void			free_texture_data(t_textures *texture_data);
void			free_game(t_game *game);
// FNC --END
void			print_subarrays(char **map);

// CONFIG
int				calculate_block_size(int width, int height, int rows, int columns);

#endif
