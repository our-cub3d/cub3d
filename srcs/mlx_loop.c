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
	draw_screen(game);
	draw_minimap(game);

	/* minimap */
	draw_rectangles(game);
	mlx_put_image_to_window(game->mlx, game->mlx->win_ptr, \
							game->minimap->img_ptr, \
							WIN_W - (game->parsing_info->width * TILE_SIZE), \
							WIN_H - (game->parsing_info->height * TILE_SIZE));
	return (0);
}
