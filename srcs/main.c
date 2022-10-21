#include "../include/cub3d.h"
#include <stdio.h>
#include "../mlx/mlx.h"

int	main(int ac, char **av)
{
	t_game	game;
	// char	*array[4];

	check_arguments(ac, av);
	init_all(&game);
	read_map(av[1], &game); //유효성 검사 및 파싱
	init_mlx(&game);
	
	game.screen->img_ptr = mlx_new_image(game.mlx->mlx_ptr, WIN_W, WIN_H);
	mlx_hook(game.mlx->win_ptr, X_EVENT_KEY_PRESS, 0, &deal_key, &game);
	mlx_hook(game.mlx->win_ptr, X_EVENT_KEY_EXIT, 0, &ft_close, &game);
	mlx_loop_hook(game.mlx->mlx_ptr, &main_loop, &game);
	mlx_loop(game.mlx->mlx_ptr);
	// printf("f: %llx c: %llx\n", game.cube_info->F, game.cube_info->C);
	// print_cube_info(game.cube_info);
	// printf("width: %d height : %d\n", game.parsing_info->width, game.parsing_info->height);
	// while (1);
}
