#include "../include/cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

int	count_in_cube_info(t_cube_info *cube_info)
{
	int	count;

	count = 0;
	if (cube_info->NO)
		++count;
	if (cube_info->SO)
		++count;
	if (cube_info->WE)
		++count;
	if (cube_info->EA)
		++count;
	if (cube_info->F)
		++count;
	if (cube_info->C)
		++count;
	return (count);
}

char	*get_front_splited(char *line, char *set)
{
	char **splited;

	splited = ft_split(line, set);
	free(splited[1]);
	free(splited);
	return (splited[0]);
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
		else if (read_wall_texture(line, game) == -2)
			print_error_and_exit("wrong information\n");
		free(line);
		line = get_next_line(fd);
	}
	// print_cube_info(game->cube_info);
	check_valid_map(line, game->parsing_info, fd); //맵의 유효성 검사. 양 끝단, 스페이스 전 좌우 비교
	close(fd);
	fd = open(name_of_map, O_RDONLY);
	get_map_array(game, fd);
	close(fd);
	print_map(game);
	//fd = open(name_of_map, O_RDONLY);// malloc 해서 파싱-> 플레이어가 2개 이상인 경우 검사. 플레이어가 없거나
}
