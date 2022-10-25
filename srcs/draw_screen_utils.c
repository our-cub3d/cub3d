/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehwkim <jaehwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:26:29 by jaehwkim          #+#    #+#             */
/*   Updated: 2022/10/24 14:36:55 by jaehwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../mlx/mlx.h"
#include <math.h>

void	init_raycating(t_game *game, t_raycasting *info, int x)
{
	info->camera_x = 2 * x / (double)WIN_W - 1;
	info->ray_dir_x = game->player->dir_x + \
					game->player->plane_x * info->camera_x;
	info->ray_dir_y = game->player->dir_y + \
					game->player->plane_y * info->camera_x;
	info->map_x = (int)game->player->pos_x;
	info->map_y = (int)game->player->pos_y;
	info->delta_x = fabs(1 / info->ray_dir_x);
	info->delta_y = fabs(1 / info->ray_dir_y);
}

void	init_step_and_side_dist(t_game *game, t_raycasting *info)
{
	if (info->ray_dir_x < 0)
	{
		info->step_x = -1;
		info->side_dist_x = (game->player->pos_x - info->map_x) \
							* info->delta_x;
	}
	else
	{
		info->step_x = 1;
		info->side_dist_x = (info->map_x + 1.0 - game->player->pos_x) \
							* info->delta_x;
	}
	if (info->ray_dir_y < 0)
	{
		info->step_y = -1;
		info->side_dist_y = (game->player->pos_y - info->map_y) \
							* info->delta_y;
	}
	else
	{
		info->step_y = 1;
		info->side_dist_y = (info->map_y + 1.0 - game->player->pos_y) \
							* info->delta_y;
	}
}

void	init_tex(t_tex *tex)
{
	tex->pos = 0;
	tex->x = 0;
	tex->y = 0;
}

void	init_screen_image(t_game *game)
{
	t_img	*screen;
	int		index;

	screen = game->screen;
	screen->img_ptr = mlx_new_image(game->mlx->mlx_ptr, WIN_W, WIN_H);
	screen->img_data = (int *)mlx_get_data_addr \
		(screen->img_ptr, &screen->bpp, &screen->size_l, &screen->endian);
	index = 0;
	while (index < WIN_H * WIN_W / 2)
	{
		screen->img_data[index] = game->cube_info->c;
		++index;
	}
	while (index < WIN_H * WIN_W)
	{
		screen->img_data[index] = game->cube_info->f;
		++index;
	}
}

double	make_wall_x(t_game *game, t_raycasting *info, int *side, double wall_x)
{
	if (*side == 0)
		wall_x = game->player->pos_y + info->perp_wall_dist * info->ray_dir_y;
	else
		wall_x = game->player->pos_x + info->perp_wall_dist * info->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}
