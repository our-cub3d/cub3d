/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehwkim <jaehwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:26:39 by jaehwkim          #+#    #+#             */
/*   Updated: 2022/10/25 10:53:41 by jaehwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../libft/libft.h"
#include "../mlx/mlx.h"

void	init_map_array(t_parsing_info *parsing_info)
{
	char	**map;
	int		y;

	map = ft_calloc(parsing_info->height, sizeof(char *));
	y = 0;
	while (y < parsing_info->height)
	{
		map[y] = ft_calloc(parsing_info->width + 1, sizeof(char));
		++y;
	}
	parsing_info->map = map;
}

void	load_xpm(t_game *game, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	img->img_ptr = mlx_xpm_file_to_image(game->mlx->mlx_ptr, path, \
						&img->img_width, &img->img_height);
	if (img->img_ptr == NULL)
		print_error_and_exit("wrong information\n");
	img->img_data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, \
							&img->size_l, &img->endian);
	y = 0;
	if (img->img_height != 64 || img->img_width != 64)
		print_error_and_exit("wrong infomation\n");
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = \
						img->img_data[img->img_width * y + x];
			++x;
		}
		++y;
	}
	mlx_destroy_image(game->mlx->mlx_ptr, img->img_ptr);
}

void	load_texture(t_game	*game)
{
	t_img	img;
	int		x;

	x = 0;
	while (x < 4)
	{
		game->wall_texture[x] = calloc(TEX_SIZE * TEX_SIZE, sizeof(int));
		++x;
	}
	load_xpm(game, game->wall_texture[0], game->cube_info->no, &img);
	load_xpm(game, game->wall_texture[1], game->cube_info->so, &img);
	load_xpm(game, game->wall_texture[2], game->cube_info->we, &img);
	load_xpm(game, game->wall_texture[3], game->cube_info->ea, &img);
}

void	init_mlx(t_game *game)
{
	t_mlx	*mlx;

	game->mlx = ft_calloc(1, sizeof(t_mlx));
	game->minimap = ft_calloc(1, sizeof(t_img));
	game->screen = ft_calloc(1, sizeof(t_img));
	mlx = game->mlx;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_W, WIN_H, "cub3d");
	load_texture(game);
	game->minimap->img_ptr = mlx_new_image(mlx->mlx_ptr, \
						TILE_SIZE * game->parsing_info->width, \
						TILE_SIZE * game->parsing_info->height);
	game->minimap->img_data = (int *)mlx_get_data_addr(game->minimap->img_ptr, \
						&(game->minimap->bpp), &(game->minimap->size_l), \
						&(game->minimap->endian));
}

void	init_all(t_game	*game)
{
	game->cube_info = ft_calloc(1, sizeof(t_cube_info));
	game->cube_info->f = -1;
	game->cube_info->c = -1;
	game->player = ft_calloc(1, sizeof(t_player));
	game->parsing_info = ft_calloc(1, sizeof(t_parsing_info));
}
