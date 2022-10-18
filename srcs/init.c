#include "../include/cub3d.h"
#include "../libft/libft.h"
#include "../mlx/mlx.h"

void	load_xpm(t_game *game, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	img->img_ptr = mlx_xpm_file_to_image(game->mlx->mlx_ptr, path, &img->img_width, &img->img_height);
	img->img_data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l, &img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->img_data[img->img_width * y + x];
			++x;
		}
		++y;
	}
	mlx_destroy_image(game->mlx->mlx_ptr, img->img_ptr);
}

void	load_texture(t_game	*game)
{
	t_img	img;

	load_xpm(game, game->wall_texture[0], game->cube_info->NO, &img);
	load_xpm(game, game->wall_texture[1], game->cube_info->SO, &img);
	load_xpm(game, game->wall_texture[2], game->cube_info->WE, &img);
	load_xpm(game, game->wall_texture[3], game->cube_info->EA, &img);
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
} // img는 파싱 후에 만듦

void	init_all(t_game	*game)
{
	game->cube_info = ft_calloc(1, sizeof(t_cube_info));
	game->cube_info->F = -1;
	game->cube_info->C = -1;
	game->player = ft_calloc(1, sizeof(t_player));
	game->parsing_info = ft_calloc(1, sizeof(t_parsing_info));
}
