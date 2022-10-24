#include "../include/cub3d.h"
#include "../libft/libft.h"

static void	screening_test(char *splited, char *temp)
{
	if (splited[0] == '0' || splited[ft_strlen(splited) - 1] == '0')
		print_error_and_exit("wrong information\n");
	if ((int)ft_strlen(splited) < (int)ft_strlen(temp))
		if (ft_strchr(&temp[(int)ft_strlen(splited)], '0'))
			print_error_and_exit("wrong information\n");
	if (!is_map(splited))
		print_error_and_exit("wrong information\n");
}

static void	check_valid_wall(char *splited, char *temp, int i)
{
	if (is_space(splited[i]))
	{
		if ((!is_space(temp[i]) && temp[i] != '1'))
			print_error_and_exit("wrong information\n");
		if (i > 0 && (!is_space(splited[i - 1]) && splited[i - 1] != '1'))
			print_error_and_exit("wrong information\n");
		if (i < (int)ft_strlen(splited) && \
			(splited[i + 1] && ((!is_space(splited[i + 1])) \
			&& splited[i + 1] != '1')))
			print_error_and_exit("wrong information\n");
	}
	else if (splited[i] != '1' && is_space(temp[i]))
		print_error_and_exit("wrong information\n");
}

static void	check_middle_line(char *splited, char *temp, \
								t_parsing_info *passing_info)
{
	int	i;

	screening_test(splited, temp);
	i = 0;
	while (splited[i])
	{
		if (i >= (int)ft_strlen(temp) && !is_space(splited[i]) && \
			splited[i] != '1')
			print_error_and_exit("wrong information\n");
		check_valid_wall(splited, temp, i);
		++i;
	}
	--i;
	if (i > passing_info->width)
		passing_info->width = i;
	++(passing_info->height);
}

static void	check_all_line(char *splited, char *temp, \
							t_parsing_info *passing_info, int fd)
{
	char	*line;

	while (splited)
	{
		check_middle_line(splited, temp, passing_info);
		free(temp);
		temp = splited;
		splited = NULL;
		line = get_next_line(fd);
		if (!line || line[0] == '\n')
		{
			is_end_line(temp);
			free(temp);
			break ;
		}
		splited = remove_newline(line, "\n");
		free(line);
	}
}

void	check_valid_map(char *line, t_parsing_info *passing_info, int fd)
{
	char	*temp;
	char	*splited;

	if (!line)
		print_error_and_exit("wrong information\n");
	passing_info->width = is_end_line(line) - 1;
	++(passing_info->height);
	temp = line;
	line = get_next_line(fd);
	splited = remove_newline(line, "\n");
	free(line);
	check_all_line(splited, temp, passing_info, fd);
}
