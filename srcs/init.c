#include "../include/cub3d.h"
#include "../libft/libft.h"
#include "../mlx/mlx.h"

static void	init_mlx(t_game *game)
{
	t_mlx	*mlx;

	game->mlx = ft_calloc(1, sizeof(t_mlx));
	mlx = game->mlx;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_W, WIN_H, "cub3d");
} // img는 파싱 후에 만듦

void	init_all(t_game	*game)
{
	game->cube_info = ft_calloc(1, sizeof(t_cube_info));
	game->cube_info->F = -1;
	game->cube_info->C = -1;
	game->player = ft_calloc(1, sizeof(t_player));
	game->parsing_info = ft_calloc(1, sizeof(t_parsing_info));
	init_mlx(game);	
}
