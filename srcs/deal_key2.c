/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:14:23 by hogkim            #+#    #+#             */
/*   Updated: 2022/10/26 14:34:18 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../mlx/mlx.h"
#include <stdlib.h>
#include <math.h>

void	deal_key_right(int key_code, t_game *game)
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

void	deal_key_left(int key_code, t_game *game)
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
