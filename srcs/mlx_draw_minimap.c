#include "../include/cub3d.h"
#include <stdio.h>
#include "../mlx/mlx.h"

static void	draw_player(t_game *game, int pos_x, int pos_y)
{
	int x;
	int y;
	int	img_w;

	pos_x *= TILE_SIZE;
	pos_y *= TILE_SIZE;
	img_w = game->parsing_info->width * TILE_SIZE;
	x = -3;
	while (-4 < x && x < 4)
	{
		y = -3;
		while ( -4 < y && y < 4)
		{
			game->minimap->img_data[(pos_y + y) * img_w + (pos_x + x)] = 0xFF00FF;
			++y;
		}
		++x;
	}
	// if (x == (h + y))
	// 		game->minimap->img_data[(h + y) * img_w + pos_x + x] = 0xFFFFFF;
}

void	draw_rectangle(t_game *game, int w, int h)
{
	int x;
	int y;
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
			game->minimap->img_data[(h  + y) * img_w + w + x] = 0xFFFFFF;
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
	draw_player(game, (int)(game->player->pos_x), (int)(game->player->pos_y));
}