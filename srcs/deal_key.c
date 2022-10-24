#include "../include/cub3d.h"
#include "../mlx/mlx.h"
#include <stdlib.h>
#include <math.h>

static void	deal_key_w(int key_code, t_game *game)
{
	(void)key_code;
	if (!game->parsing_info->map[(int)(game->player->pos_y)] \
		[(int)(game->player->pos_x + game->player->dir_x * MOV_SPEED)])
		game->player->pos_x += game->player->dir_x * MOV_SPEED;
	if (!game->parsing_info->map[(int)(game->player->pos_y \
		+ game->player->dir_y * MOV_SPEED)][(int)(game->player->pos_x)])
		game->player->pos_y += game->player->dir_y * MOV_SPEED;
}

static void	deal_key_s(int key_code, t_game *game)
{
	(void)key_code;
	if (!game->parsing_info->map[(int)(game->player->pos_y)] \
		[(int)(game->player->pos_x - game->player->dir_x * MOV_SPEED)])
		game->player->pos_x -= game->player->dir_x * MOV_SPEED;
	if (!game->parsing_info->map[(int)(game->player->pos_y - \
		game->player->dir_y * MOV_SPEED)][(int)(game->player->pos_x)])
		game->player->pos_y -= game->player->dir_y * MOV_SPEED;
}

static void	deal_key_d(int key_code, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	(void)key_code;
	old_dir_x = game->player->dir_x;
	old_plane_x = game->player->plane_x;
	game->player->dir_x = game->player->dir_x * \
		cos(ROT_SPEED) - game->player->dir_y * sin(ROT_SPEED);
	game->player->dir_y = old_dir_x * sin(ROT_SPEED) \
		+ game->player->dir_y * cos(ROT_SPEED);
	game->player->plane_x = game->player->plane_x \
		* cos(ROT_SPEED) - game->player->plane_y * sin(ROT_SPEED);
	game->player->plane_y = old_plane_x * sin(ROT_SPEED) \
		+ game->player->plane_y * cos(ROT_SPEED);
}

static void	deal_key_a(int key_code, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	(void)key_code;
	old_dir_x = game->player->dir_x;
	old_plane_x = game->player->plane_x;
	game->player->dir_x = game->player->dir_x \
		* cos(-ROT_SPEED) - game->player->dir_y * sin(-ROT_SPEED);
	game->player->dir_y = old_dir_x * sin(-ROT_SPEED) \
		+ game->player->dir_y * cos(-ROT_SPEED);
	game->player->plane_x = game->player->plane_x \
		* cos(-ROT_SPEED) - game->player->plane_y * sin(-ROT_SPEED);
	game->player->plane_y = old_plane_x * sin(-ROT_SPEED) \
		+ game->player->plane_y * cos(-ROT_SPEED);
}

int	deal_key(int key_code, t_game *game)
{
	if (key_code == KEY_W)
	{
		deal_key_w(key_code, game);
	}
	if (key_code == KEY_S)
	{
		deal_key_s(key_code, game);
	}
	if (key_code == KEY_D)
	{
		deal_key_d(key_code, game);
	}
	if (key_code == KEY_A)
	{
		deal_key_a(key_code, game);
	}
	if (key_code == KEY_ESC)
	{
		exit(0);
	}
	return (0);
}
