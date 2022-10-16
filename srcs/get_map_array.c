#include "../include/cub3d.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdio.h>

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

void	fill_element(t_game *game, char input, int x, int y)
{
	if (is_space(input))
		game->parsing_info->map[y][x] = E_VOID;
	else if (input == '1')
		game->parsing_info->map[y][x] = E_WALL;
	else if (input == '0')
		game->parsing_info->map[y][x] = E_ROAD;
	else if (input == 'N' || input == 'W' || input == 'S' || input == 'E')
	{
		if (game->player->x)
			print_error_and_exit("too many players!\n");
		if (input == 'N')
			game->player->angle = 0;
		else if (input == 'W')
			game->player->angle = M_PI / 2;
		else if (input == 'S')
			game->player->angle = M_PI;
		else if (input == 'E')
			game->player->angle = M_PI + M_PI / 2;
		game->player->x = x;
		game->player->y = y;
		game->parsing_info->map[y][x] = E_ROAD;
	}
}

		// if (game->player->x)
		// 	print_error_and_exit("too many players!\n");
		// if (input == 'N')
		// {
		// 	game->player->dirX = 0;
		// 	game->player->dirY = -1;
		// }
		// else if (input == 'W')
		// {
		// 	game->player->dirX = -1;
		// 	game->player->dirY = 0;
		// }
		// else if (input == 'S')
		// {
		// 	game->player->dirX = 0;
		// 	game->player->dirY = 1;
		// }
		// else if (input == 'E')
		// {
		// 	game->player->dirX = 1;
		// 	game->player->dirY = 0;
		// }

void	fill_map_array(t_game *game, int fd, char *line)
{
	char *temp;
	int	x;
	int	y;

	y = 0;
	temp = line;
	while (y < game->parsing_info->height)
	{
		x = 0;
		while (temp[x])
		{
			fill_element(game, temp[x], x, y);
			++x;
		}
		free(temp);
		while (x < game->parsing_info->width)
		{
			game->parsing_info->map[y][x] = E_VOID;
			++x;
		}
		++y;
		temp = get_next_line(fd);
	}
}

void	get_map_array(t_game *game, int fd)
{
	char	*line;

	init_map_array(game->parsing_info);
	line = get_next_line(fd);
	while (!is_map(line) || *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	fill_map_array(game, fd, line);
	if (game->player->x == 0)
		print_error_and_exit("there's no player!\n");
}
