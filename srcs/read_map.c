#include "../include/cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>

void	read_wall_texture(char *line)
{
	char	**splited_line;

	ft_split(line, );
}

void	read_map(char *name_of_map)
{
	char	*line;
	int		fd;

	fd = open(name_of_map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		read_wall_texture(line);
		free(line);
		line = get_next_line(fd);
	}
}