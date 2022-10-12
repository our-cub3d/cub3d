#include "../include/cub3d.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

static void	update_value(char **info, char *value)
{
	if (*info)
		print_error_and_exit("wrong information\n");
	*info = value;
}

int	compare_and_save(char **splited, t_cube_info *cube_info)
{
	if (!ft_strncmp(splited[0], "NO", 3))
		update_value(&cube_info->NO, splited[1]);
	else if (!ft_strncmp(splited[0], "SO", 3))
		update_value(&cube_info->SO, splited[1]);
	else if (!ft_strncmp(splited[0], "WE", 3))
		update_value(&cube_info->WE, splited[1]);
	else if (!ft_strncmp(splited[0], "EA", 3))
		update_value(&cube_info->EA, splited[1]);
	else if (!ft_strncmp(splited[0], "F", 2))
		update_value(&cube_info->F, splited[1]);
	else if (!ft_strncmp(splited[0], "C", 2))
		update_value(&cube_info->C, splited[1]);
	else
	{
		free(splited[0]);
		free(splited[1]);
		return (0);
	}
	free(splited[0]);
	return (1);
}

int	read_wall_texture(char *line, t_game *game)
{
	static char	spaces[7] = {'\t', '\n', '\v', '\f', '\r', ' ', 0};
	char		**splited;
	int			result;

	// printf("count : %d\n", ft_word_count(line, spaces));
	// printf("line : |%s|\n", line);
	if (ft_word_count(line, spaces) == 0)
		return (-1);
	if (ft_word_count(line, spaces) != 2)
		return (0);
	splited = ft_split(line, spaces);
	result = compare_and_save(splited, game->cube_info);
	free(splited);
	return (result);
}
