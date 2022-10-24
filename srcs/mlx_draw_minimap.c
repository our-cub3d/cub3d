#include "../include/cub3d.h"
#include <stdio.h>
#include "../mlx/mlx.h"

void	draw_player(t_game *game)
{
	int	player_x;
	int	player_y;
	int	mini_width;

	player_x = game->player->pos_x * TILE_SIZE;
	player_y = game->player->pos_y * TILE_SIZE;
	mini_width = game->parsing_info->width * TILE_SIZE;
	game->minimap->img_data[player_y * mini_width + player_x] = 0xFF00FF;
	game->minimap->img_data[(player_y - 1) * mini_width + player_x] = 0xFF00FF;
	game->minimap->img_data[(player_y + 1) * mini_width + player_x] = 0xFF00FF;
	game->minimap->img_data[player_y * mini_width + player_x - 1] = 0xFF00FF;
	game->minimap->img_data[player_y * mini_width + player_x + 1] = 0xFF00FF;
}

void	draw_rectangle(t_game *game, int w, int h)
{
	int	x;
	int	y;
	int	img_w;

	w *= TILE_SIZE;
	h *= TILE_SIZE;
	img_w = game->parsing_info->width * TILE_SIZE;
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			game->minimap->img_data[(h + y) * img_w + w + x] = 0xFFFFFF;
			++x;
		}
		++y;
	}
}

void	draw_rectangles(t_game *game)
{
	int		h;
	int		w;

	h = 0;
	while (h < game->parsing_info->height)
	{
		w = 0;
		while (w < game->parsing_info->width)
		{
			if (game->parsing_info->map[h][w] == E_WALL)
				draw_rectangle(game, w, h);
			++w;
		}
		++h;
	}
	draw_player(game);
}

void	draw_minimap(t_game *game)
{
	mlx_destroy_image(game->mlx->mlx_ptr, game->minimap->img_ptr);
	game->minimap->img_ptr = mlx_new_image(game->mlx->mlx_ptr, \
						TILE_SIZE * game->parsing_info->width, \
						TILE_SIZE * game->parsing_info->height);
	game->minimap->img_data = (int *)mlx_get_data_addr(game->minimap->img_ptr, \
						&(game->minimap->bpp), &(game->minimap->size_l), \
						&(game->minimap->endian));
	draw_rectangles(game);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr, \
							game->minimap->img_ptr, \
							WIN_W - (game->parsing_info->width * TILE_SIZE), \
							WIN_H - (game->parsing_info->height * TILE_SIZE));
}
