#include "../../include/cub3d.h"
#include "../../mlx/mlx.h"
#include <math.h>

static void	init_raycating(t_game *game, t_raycasting *info, int x)
{
	info->camera_x = 2 * x / (double)WIN_W - 1;
	info->ray_dir_x = game->player->dir_x + game->player->plane_x * info->camera_x;
	info->ray_dir_y = game->player->dir_y + game->player->plane_y * info->camera_x;
	info->map_x = (int)game->player->pos_x;
	info->map_y = (int)game->player->pos_y;
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
			info->side_dist_x += info->delta_x;
			info->map_x += info->step_x;
			*side = 0;
		}
		else
		{
			info->side_dist_y += info->delta_y;
			info->map_y += info->step_y;
			*side = 1;
		}
		if (game->parsing_info->map[info->map_y][info->map_x] == E_WALL)
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
	info->draw_start = -info->line_height / 2 + WIN_H / 2;
	if (info->draw_start < 0)
		info->draw_start = 0;
	info->draw_end = info->line_height / 2 + WIN_H / 2;
	if (info->draw_end >= WIN_H)
		info->draw_end = WIN_H - 1;
}

static void	init_tex(t_tex *tex)
{
	tex->pos = 0;
	tex->x = 0;
	tex->y = 0;
}

static void	painting_wall(t_game *game, t_raycasting *info, int *side, int x)
{
	double	wall_x;
	double	step;
	t_tex	tex;
	int		y;
	
	init_tex(&tex);
	if (*side == 0)
		wall_x = game->player->pos_y + info->perp_wall_dist * info->ray_dir_y;
	else
		wall_x = game->player->pos_x + info->perp_wall_dist * info->ray_dir_x;
	wall_x -= floor(wall_x);
	tex.x = (int)(wall_x * (double)TEX_SIZE);
	if (*side == 0 && info->ray_dir_x < 0)
		tex.x = TEX_SIZE - tex.x - 1;
	if (*side == 1 && info->ray_dir_y > 0)
		tex.x = TEX_SIZE - tex.x - 1;
	step = 1.0 * TEX_SIZE / info->line_height;
	tex.pos = (info->draw_start - WIN_H / 2 + info->line_height / 2) * step;
	y = info->draw_start;
	while (y < info->draw_end)
	{
		tex.y = (int)tex.pos & (TEX_SIZE - 1);
		tex.pos += step;
		game->screen->img_data[WIN_W * y + x] = game->wall_texture[info->tex_num][TEX_SIZE * tex.y + tex.x];
		++y;
	}
}

static void	get_tex_num(t_raycasting *info, int *side)
{
	if (*side == 0)
	{
		if (info->ray_dir_x < 0)
			info->tex_num = D_EA;
		else
			info->tex_num = D_WE;
	}
	else
	{
		if (info->ray_dir_y < 0)
			info->tex_num = D_SO;
		else
			info->tex_num = D_NO;
	}
}

static void	init_screen_image(t_game *game)
{
	t_img	*screen;
	int		index;

	screen = game->screen;
	screen->img_ptr = mlx_new_image(game->mlx->mlx_ptr, WIN_W, WIN_H);
	screen->img_data = (int *)mlx_get_data_addr(screen->img_ptr, \
												&screen->bpp, &screen->size_l, &screen->endian);
	index = 0;
	while (index < WIN_H * WIN_W / 2)
	{
		screen->img_data[index] = game->cube_info->C;
		++index;
	}
	while (index < WIN_H * WIN_W)
	{
		screen->img_data[index] = game->cube_info->F;
		++index;
	}
}

void	draw_screen(t_game *game)
{
	int				x;
	int				side;
	t_raycasting	info;

	mlx_destroy_image(game->mlx->mlx_ptr, game->screen->img_ptr);
	init_screen_image(game);
	x = 0;
	while (x < WIN_W)
	{
		init_raycating(game, &info, x);
		init_step_and_side_dist(game, &info);
		side = 0;
		follow_ray_dda(game, &info, &side);
		get_wall_height(&info, game->player, &side);
		get_tex_num(&info, &side);
		painting_wall(game, &info, &side, x);
		++x;
	}
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->win_ptr, game->screen->img_ptr, 0, 0);
}
