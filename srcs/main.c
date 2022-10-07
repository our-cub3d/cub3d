#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	check_arguments(ac, av);
	init_all(&game);
	read_map(av[1], &game); //유효성 검사 및 파싱
	// print_map();
}
