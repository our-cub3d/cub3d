#include "../include/cub3d.h"
#include <stdio.h>

void	print_map(t_game *game)
{
	for (int y = 0; y < game->parsing_info->height; ++y)
	{
		for (int x = 0; x < game->parsing_info->width; ++x)
		{
			printf("%d", game->parsing_info->map[y][x]);
		}
		printf("\n");
	}

	// printf("\n\n");
	// printf("player : %f, %d, %d\n", game->player->angle, game->player->pos_x, game->player->pos_y);
}

void print_cube_info(t_cube_info *cube)
{
	printf("NO : %s\n", cube->NO);
	printf("SO : %s\n", cube->SO);
	printf("WE : %s\n", cube->WE);
	printf("EA : %s\n", cube->EA);
	printf("F : %lld\n", cube->F);
	printf("C : %lld\n", cube->C);
}
