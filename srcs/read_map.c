/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:14:48 by hogkim            #+#    #+#             */
/*   Updated: 2022/10/24 21:28:25 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

int	count_in_cube_info(t_cube_info *cube_info)
{
	int	count;

	count = 0;
	if (cube_info->no)
		++count;
	if (cube_info->so)
		++count;
	if (cube_info->we)
		++count;
	if (cube_info->ea)
		++count;
	if (cube_info->f != -1)
		++count;
	if (cube_info->c != -1)
		++count;
	return (count);
}

void	read_map(char *name_of_map, t_game *game)
{
	char		*line;
	int			fd;

	fd = open(name_of_map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (read_wall_texture(line, game) == 0)
		{
			if (!is_map(line) || count_in_cube_info(game->cube_info) != 6)
				print_error_and_exit("wrong information\n");
			else
				break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	check_valid_map(line, game->parsing_info, fd);
	close(fd);
	fd = open(name_of_map, O_RDONLY);
	get_map_array(game, fd);
	close(fd);
}
