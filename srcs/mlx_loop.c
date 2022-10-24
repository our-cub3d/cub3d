#include "../include/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../mlx/mlx.h"

int	ft_close(t_game *game)
{
	(void)game;
	exit(0);
}

int	main_loop(t_game *game)
{
	draw_screen(game);
	draw_minimap(game);
	return (0);
}
