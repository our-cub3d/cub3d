#include "../include/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include "../mlx/mlx.h"

int		deal_key(int key_code, t_game *game)
{
	(void)game;
	if (key_code == KEY_ESC)
		exit(0);
	return (0);
}

int 	ft_close(t_game *game)
{
	(void)game;
	exit(0);
}

int		main_loop(t_game *game)
{
	draw_rectangles(game);
	// draw_lines(game);
	mlx_put_image_to_window(game->mlx, game->mlx->win_ptr, game->mlx->img_minimap.img_ptr, 500, 400);
	return (0);
}
