/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehwkim <jaehwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:26:46 by jaehwkim          #+#    #+#             */
/*   Updated: 2022/10/25 15:32:46 by jaehwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>
#include "../mlx/mlx.h"

int	ft_close(t_game *game)
{
	(void)game;
	exit(0);
}

int	main_loop(t_game *game)
{
	draw_screen(game);
	draw_minimap(game);
	return (0);
}
