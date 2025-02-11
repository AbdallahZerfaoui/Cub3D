#ifndef TEST_HEADERFILE_H
# define TEST_HEADERFILE_H

# define WIDTH 516
# define HEIGHT 516
# define PI 3.14159265359

// Includes -- BEGIN
# include "../MLX42/include/MLX42/MLX42.h"
# include "../lib/lib.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
// Includes -- END

typedef struct s_point
{
	bool		key_up;
	bool		key_right;
	bool		key_left;
	bool		key_down;
	// bool		left_rotate;
	// bool		right_rotate;
	float			x;
	float			y;
}				t_point;

typedef struct s_game
{
	mlx_t		*mlx;
	char		map[12][12];
	int			collectibles_collected;
	t_point		*player_coords;
	mlx_image_t	*player;

	void		*win;
	void		*img;

	int			*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_game;

// FNC --BEGIN
void			printHello(void);
void			alo(void);
// FNC --END
#endif
