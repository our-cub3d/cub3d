#include "../../include/cub3d.h"
#include <math.h>

static void	init_raycating(t_game *game, t_raycasting *info)
{
	info->camera_x = 2 * x / (double)info->WIN_W - 1;
	info->ray_dir_x = game->player->dir_x + game->player->dir_x * info->camera_x;
	info->ray_dir_y = game->player->dir_x + game->player->dir_y * info->camera_x;
	info->map_x = (int)game->player->pos_x;
	info->map_x = (int)game->player->pos_y;
	info->delta_x = fabs(1 / info->ray_dir_x);
	info->delta_y = fabs(1 / info->ray_dir_y);
}

static void	init_step_and_side_dist(t_game *game, t_raycasting *info)
{
	if (info->ray_dir_x < 0)
		{
			info->step_x = -1;
			info->side_dist_x = (game->player->pos_x - info->map_x) * info->delta_x;
		}
		else
		{
			info->step_x = 1;
			info->side_dist_x = (info->map_x + 1.0 - game->player->pos_x) * info->delta_x;
		}
		if (info->ray_dir_y < 0)
		{
			info->step_y = -1;
			info->side_dist_y = (game->player->pos_y - info->map_y) * info->delta_y;
		}
		else
		{
			info->step_y = 1;
			info->side_dist_y = (info->map_y + 1.0 - game->player->pos_y) * info->delta_y;
		}
}

void	draw_screen(t_game *game)
{
	int				x;
	int				hit;
	int				side;
	t_raycasting	info;

	x = 0;
	while (x < WIN_W)
	{
		init_raycating(game, &info);
		hit = 0;
		init_step_and_side_dist(game, &info);

//---------------------------------------------------------------------
		// dda
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / ray_dir_x;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		// 그림 크기 정하기
		int lineHeight = (int)(height / perpWallDist);

		int drawStart = -lineHeight / 2 + height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if(drawEnd >= height)
			drawEnd = height - 1;

		int texNum = worldMap[mapX][mapY] - 1;

		double wallX;
		if (side == 0)
			wallX = info->posY + perpWallDist * rayDirY;
			wallX = info->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		double step = 1.0 * texHeight / lineHeight;

		// Starting texture coordinate
		double texPos = (drawStart - height / 2 + lineHeight / 2) * step;

		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;

			int color = info->texture[texNum][texHeight * texY + texX];

			if (side == 1)
				color = (color >> 1) & 8355711;

			info->buf[y][x] = color;
		}
		x++;
	}
}
