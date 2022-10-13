#include "../include/cub3d.h"
#include "../libft/libft.h"
#include "../mlx/mlx.h"

void	init_mlx(t_game *game)
{
	t_mlx	*mlx;

	game->mlx = ft_calloc(1, sizeof(t_mlx));
	mlx = game->mlx;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_W, WIN_H, "cub3d");
	mlx->img_minimap.img_ptr = mlx_new_image(mlx->mlx_ptr, \
						TILE_SIZE * game->parsing_info->width, \
						TILE_SIZE * game->parsing_info->height);
	mlx->img_minimap.img_data = (int *)mlx_get_data_addr(mlx->img_minimap.img_ptr, \
						&(mlx->img_minimap.bpp), &(mlx->img_minimap.size_l), \
						&(mlx->img_minimap.endian));
} // img는 파싱 후에 만듦

void	init_all(t_game	*game)
{
	game->cube_info = ft_calloc(1, sizeof(t_cube_info));
	game->cube_info->F = -1;
	game->cube_info->C = -1;
	game->player = ft_calloc(1, sizeof(t_player));
	game->parsing_info = ft_calloc(1, sizeof(t_parsing_info));
}
