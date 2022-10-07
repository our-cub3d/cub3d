#include "cub3d.h"

int	main(int ac, char **av)
{
	check_arguments(ac, av);
	init_all();
	read_map(av[1]);
	print_map();
}