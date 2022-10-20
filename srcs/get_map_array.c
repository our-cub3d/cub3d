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

static void	get_player_dir(t_game *game, char input)
{
	if (input == 'N')// 
	{
		game->player->dir_x = 0;
		game->player->dir_y = -1.0;
		game->player->plane_x = 0.66;
		game->player->plane_y = 0;
	}
	else if (input == 'W')
	{
		game->player->dir_x = -1.0;
		game->player->dir_y = 0;
		game->player->plane_x = 0;
		game->player->plane_y = -0.66;
	}
	else if (input == 'S')
	{
		game->player->dir_x = 0;
		game->player->dir_y = 1.0;
		game->player->plane_x = -0.66;
		game->player->plane_y = 0;
	}
	else if (input == 'E')
	{
		game->player->dir_x = 1.0;
		game->player->dir_y = 0;
		game->player->plane_x = 0;
		game->player->plane_y = 0.66;
	}
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
		if (game->player->pos_y)
			print_error_and_exit("too many players!\n");
		get_player_dir(game, input);
		game->player->pos_x = x + 0.5;
		game->player->pos_y = y + 0.5;
		game->parsing_info->map[y][x] = E_ROAD;
	}
}

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
		temp = NULL;
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
	if (game->player->pos_x == 0)
		print_error_and_exit("there's no player!\n");
}
