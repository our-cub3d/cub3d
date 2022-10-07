#include "../include/cub3d.h"
#include "../libft/libft.h"

void	check_arguments(int argc, char **argv)
{
	int	i;

	if (argc != 2)
		print_error_and_exit("wrong arguments\n");
	i = ft_strlen(argv[1]) - 1;
	while (argv[1][i] != '.')
	{
		if (i == 0)
			print_error_and_exit("wrong file\n");
		--i;
	}
	if (ft_strncmp(argv[1] + i, ".cub\0", 5) != 0)
		print_error_and_exit("wrong name\n");
}
