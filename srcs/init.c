#include "../include/cub3d.h"
#include "../libft/libft.h"

void	init_all(t_game	*game)
{
	game->cube_info = ft_calloc(1, sizeof(t_cube_info));
	game->cube_info->F = -1;
	game->cube_info->C = -1;
	game->player = ft_calloc(1, sizeof(t_player));
	game->parsing_info = ft_calloc(1, sizeof(t_parsing_info));
}
