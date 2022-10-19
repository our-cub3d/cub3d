#include "../../include/cub3d.h"
#include <math.h>

static void	init_raycating(t_game *game, t_raycasting *info, int x)
{
	info->camera_x = 2 * x / (double)WIN_W - 1;
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

static void	follow_ray_dda(t_game *game, t_raycasting *info, int *side)
{
	int hit;
	
	hit = 0;
	while (hit == 0)
	{
		if (info->side_dist_x < info->side_dist_y)
		{
			info->side_dist_x += info->side_dist_x;
			info->map_x += info->step_x;
			*side = 0;
		}
		else
		{
			info->side_dist_y += info->side_dist_y;
			info->map_y += info->step_y;
			*side = 1;
		}
		if (game->parsing_info->map[info->map_x][info->map_y] > 0)
			hit = 1;
	}
}

static void	get_wall_height(t_raycasting *info, t_player *player, int *side)
{
	if (*side == 0)
		info->perp_wall_dist = (info->map_x - player->pos_x + \
								(1 - info->step_x) / 2) / info->ray_dir_x;
	else
		info->perp_wall_dist = (info->map_y - player->pos_y + \
								(1 - info->step_y) / 2) / info->ray_dir_y;
	info->line_height = (int)(WIN_H / info->perp_wall_dist);
	info->draw_start = -info->line_height / 2 + WIN_H/ 2;
	if (info->draw_start < 0)
		info->draw_start = 0;
	info->draw_end = info->line_height / 2 + WIN_H / 2;
	if (info->draw_end >= WIN_H)
		info->draw_end = WIN_H - 1;
}

static void	painting_wall(t_game *game, t_raycasting *info, int *side)
{
	double	wall_x;
	double	step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
	int		y;
	
	if (*side == 0)
		wall_x = game->player->pos_y + info->perp_wall_dist * info->ray_dir_y;
	else
		wall_x = game->player->pos_x + info->perp_wall_dist * info->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEX_SIZE);
	if (*side == 0 && info->ray_dir_x > 0)
		tex_x = TEX_SIZE - tex_x - 1;
	if (*side == 1 && info->ray_dir_y < 0)
		tex_x = TEX_SIZE - tex_x - 1;
	step = 1.0 * TEX_SIZE / info->line_height;
	tex_pos = (info->draw_start - WIN_H / 2 + info->line_height / 2) * step;

	y = info->draw_start;
	while (y < info->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_SIZE - 1);
		tex_pos += step;
		// 여기 확인
		game->screen->img_data[y][x] = game->wall_texture[info->tex_num][TEX_SIZE * tex_y + tex_x];
		++y;
	}
}

void	draw_screen(t_game *game)
{
	int				x;
	int				side;
	t_raycasting	info;

	//스크린 이미지 하나 만들고 천장, 바닥 칠한 상태 만들고
	x = 0;
	while (x < WIN_W)
	{
		init_raycating(game, &info, x);
		init_step_and_side_dist(game, &info);
		side = 0;
		follow_ray_dda(game, &info, &side);
		get_wall_height(&info, game->player, &side);
//---------------------------------------------------------------------//

		int texNum = worldMap[mapX][mapY] - 1; //동서남북 텍스쳐 판별

//---------------------------------------------------------------------//
		painting_wall(game, &info, &side);
		x++;
	}
	//put_image 들어올 곳.
}
