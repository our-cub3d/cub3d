#include "../include/cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>

int	count_null_in_cube_info(t_cube_info *cube_info)
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

int	compare_and_save(char **splited, t_cube_info *cube_info)
{
	if (!ft_strncmp(splited[0], "NO", 3))
		cube_info->NO = splited[1];
	else if (!ft_strncmp(splited[0], "SO", 3))
		cube_info->SO = splited[1];
	else if (!ft_strncmp(splited[0], "WE", 3))
		cube_info->WE = splited[1];
	else if (!ft_strncmp(splited[0], "EA", 3))
		cube_info->EA = splited[1];
	else if (!ft_strncmp(splited[0], "F", 2))
		cube_info->F = splited[1];	
	else if (!ft_strncmp(splited[0], "C", 2))
		cube_info->C = splited[1];
	else
	{
		// print_error_and_exit("wrong information\n");
		return (0);
	}
	free(splited[0]);
	return (1);
}

void	read_wall_texture(char *line, t_game *game)
{
	static char	spaces[7] = {'\t', '\n', '\v', '\f', '\r', ' ', 0};
	char		**splited;

	if (ft_word_count(line, spaces) == 0)
		return ;
	if (ft_word_count(line, spaces) != 2)
		print_error_and_exit("wrong information\n");
	splited = ft_split(line, spaces);
	compare_and_save(splited, game->cube_info);
	free(splited);
}

void	read_map(char *name_of_map, t_game *game)
{
	char	*line;
	int		fd;

	fd = open(name_of_map, O_RDONLY);// open 해서 유효성 검사
	line = get_next_line(fd);
	while (line)
	{
		read_wall_texture(line, game);
		//if (read_wall_texture(line, game));
		free(line);
		line = get_next_line(fd);
	}
	//fd = open(name_of_map, O_RDONLY);// malloc 해서 파싱

}
