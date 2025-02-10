#ifndef TEST_HEADERFILE_H
# define TEST_HEADERFILE_H

# define WIDTH 516
# define HEIGHT 516

// Includes -- BEGIN
# include "../MLX42/include/MLX42/MLX42.h"
# include "../lib/lib.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
// Includes -- END

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_game
{
	mlx_t	*mlx;
	char	map[12][12];
	int		collectibles_collected;
	t_point	player_coords;
}			t_game;

// FNC --BEGIN
void		printHello(void);
void		alo(void);
// FNC --END
#endif
