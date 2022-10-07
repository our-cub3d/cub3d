#include "../include/cub3d.h"
#include <stdio.h>

void print_cube_info(t_cube_info *cube)
{
	printf("NO : %s\n", cube->NO);
	printf("SO : %s\n", cube->SO);
	printf("WE : %s\n", cube->WE);
	printf("EA : %s\n", cube->EA);
	printf("F : %s\n", cube->F);
	printf("C : %s\n", cube->C);
}

int	main(int ac, char **av)
{
	t_game	game;

	check_arguments(ac, av);
	init_all(&game);
	read_map(av[1], &game); //유효성 검사 및 파싱
	print_cube_info(game.cube_info);
		// printf("%s %s :")
	// print_map();
}
