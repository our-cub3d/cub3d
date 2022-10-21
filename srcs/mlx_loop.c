#include "../include/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../mlx/mlx.h"

int		deal_key(int key_code, t_game *game)
{
	if (key_code == KEY_W)
	{
		if (!game->parsing_info->map[(int)(game->player->pos_y)][(int)(game->player->pos_x + game->player->dir_x * MOV_SPEED)])
			game->player->pos_x += game->player->dir_x * MOV_SPEED;
		if (!game->parsing_info->map[(int)(game->player->pos_y + game->player->dir_y * MOV_SPEED)][(int)(game->player->pos_x)])
			game->player->pos_y += game->player->dir_y * MOV_SPEED;
	}
	if (key_code == KEY_S)
	{
		if (!game->parsing_info->map[(int)(game->player->pos_y)][(int)(game->player->pos_x - game->player->dir_x * MOV_SPEED)])
			game->player->pos_x -= game->player->dir_x * MOV_SPEED;
		if (!game->parsing_info->map[(int)(game->player->pos_y - game->player->dir_y * MOV_SPEED)][(int)(game->player->pos_x)])
			game->player->pos_y -= game->player->dir_y * MOV_SPEED;
	}
	if (key_code == KEY_D)
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(ROT_SPEED) - game->player->dir_y * sin(ROT_SPEED);
		game->player->dir_y = oldDirX * sin(ROT_SPEED) + game->player->dir_y * cos(ROT_SPEED);
		double oldPlaneX = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(ROT_SPEED) - game->player->plane_y * sin(ROT_SPEED);
		game->player->plane_y = oldPlaneX * sin(ROT_SPEED) + game->player->plane_y * cos(ROT_SPEED);
	}
	if (key_code == KEY_A)
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-ROT_SPEED) - game->player->dir_y * sin(-ROT_SPEED);
		game->player->dir_y = oldDirX * sin(-ROT_SPEED) + game->player->dir_y * cos(-ROT_SPEED);
		double oldPlaneX = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(-ROT_SPEED) - game->player->plane_y * sin(-ROT_SPEED);
		game->player->plane_y = oldPlaneX * sin(-ROT_SPEED) + game->player->plane_y * cos(-ROT_SPEED);
	}
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
	// draw_minimap(game);

	/* minimap */
	draw_rectangles(game); // 밖으로 빼기
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr, \
							game->minimap->img_ptr, \
							WIN_W - (game->parsing_info->width * TILE_SIZE), \
							WIN_H - (game->parsing_info->height * TILE_SIZE));
	// mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr, \
	// 				WIN_W - (game->parsing_info->width * TILE_SIZE) + game->parsing_info->width * game->player->pos_x, \
	// 				WIN_H - (game->parsing_info->height * TILE_SIZE) + game->parsing_info->height * game->player->pos_y, \
	// 				0xFF00FF, "JKKKKKK");
	// mlx_pixel_put(game->mlx->mlx_ptr, game->mlx->win_ptr, WIN_W - (game->parsing_info->width * TILE_SIZE) + game->parsing_info->width * game->player->pos_x, \
	// 				WIN_H - (game->parsing_info->height * TILE_SIZE) + game->parsing_info->height * game->player->pos_y, 0xFF00FF);
	// mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr, 0 , 0 + 3, 0xFF00FF, ".");
	mlx_string_put(game->mlx->mlx_ptr, game->mlx->win_ptr, WIN_W - (game->parsing_info->width * TILE_SIZE) + game->player->pos_x * TILE_SIZE, WIN_H - (game->parsing_info->height * TILE_SIZE) + game->player->pos_y * TILE_SIZE,\
					0xFF00FF, ".");
	return (0);
}
