#include <unistd.h>

void	put_string_fd(char *str, int fd)
{
	int	len;

	len = 0;
	while(str[len])
		++len;
	write(fd, str,len);
}

void	print_error_and_exit(char *str)
{
	put_string_fd(str, 2);
	exit(1);
}

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

int	main(int ac, char **av)
{
	check_arguments(ac, av);
	init_all();
	read_map(av[1]);
	print_map();
}