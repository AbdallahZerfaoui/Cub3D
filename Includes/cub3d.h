#ifndef TEST_HEADERFILE_H
# define TEST_HEADERFILE_H

# define WIDTH 516
# define HEIGHT 516
# define ROW_COLUMN_COUNT 12
# define BLOCK_SIZE 43 // Because WIDTH / ROW_COLUMN_COUNT (516 / 12)
# define PI 3.14159265359
# define ANGLE_OF_VIEW 60

// Includes -- BEGIN
# include "../MLX42/include/MLX42/MLX42.h"
# include "../lib/lib.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
// Includes -- END

typedef struct s_point
{
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

typedef struct s_game
{
	mlx_t		*mlx;
	char		map[12][12];
	t_point		*player_data;
	mlx_image_t	*background;
	mlx_image_t	*wall;
}				t_game;

// FNC --BEGIN
void			printHello(void);
bool			check_wall(float px, float py, t_game *game);
// PARSING
void			parse_map(t_game *game);
// INITIALIZE
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
t_game			*initialize_game_data(void);
// RAYCASTING
void			draw_single_ray(t_game *game, t_point *player_data,
					float ray_angle, float ray_count);
// MOVEMENT
// key_handle.c
void			handle_key_press(struct mlx_key_data keydata, t_game *game);
void			handle_key_release(struct mlx_key_data keydata, t_game *game);
// move.c
void			handle_movement(t_game *game, t_point *player_data);
void			clear_image(t_game *game);
void			draw_square(float x, float y, int size, t_game *game);
bool			check_wall(float px, float py, t_game *game);
// FNC --END
#endif
