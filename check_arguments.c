#include "cub3d.h"

void	check_arguments(int argc, char **argv)
{
	int	i;

	if (argc != 2)
		print_error_and_exit("Error!\nwrong arguments\n");
	i = 0;
	//확장자 이름 확인
	while (argv[1][i] != '.')
	{
		if (argv[1][i] == '\0')
			print_error_and_exit("Error!\nwrong file\n");
		i++;
	}
	if (ft_strncmp(argv[1] + i, ".cub\0", 5) != 0)
		print_error_and_exit("Error!\nwrong name\n");
}
