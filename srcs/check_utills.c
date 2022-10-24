#include "../include/cub3d.h"
#include "../libft/libft.h"

char	*remove_newline(char *line, char *set)
{
	char	**splited;

	splited = ft_split(line, set);
	free(splited[1]);
	free(splited);
	return (splited[0]);
}
