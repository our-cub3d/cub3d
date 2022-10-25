/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehwkim <jaehwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:26:32 by jaehwkim          #+#    #+#             */
/*   Updated: 2022/10/24 14:27:14 by jaehwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>

static void	follow_ray_dda(t_game *game, t_raycasting *info, int *side)
{
	int	hit;

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

static void	painting_wall(t_game *game, t_raycasting *info, int *side, int x)
{
	double	wall_x;
	double	step;
	t_tex	tex;
	int		y;

	init_tex(&tex);
	wall_x = 0;
	wall_x = make_wall_x(game, info, side, wall_x);
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
		game->screen->img_data[WIN_W * y + x] = \
				game->wall_texture[info->tex_num][TEX_SIZE * tex.y + tex.x];
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
	mlx_put_image_to_window(game->mlx->mlx_ptr, \
						game->mlx->win_ptr, game->screen->img_ptr, 0, 0);
}
