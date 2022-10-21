#include "../include/cub3d.h"
#include "../libft/libft.h"

char	*remove_newline(char *line, char *set)
{
	char **splited;

	splited = ft_split(line, set);
	free(splited[1]);
	free(splited);
	return (splited[0]);
}

static void	screening_test(char *splited, char *temp)
{
	if (splited[0] == '0' || splited[ft_strlen(splited) - 1] == '0')
		print_error_and_exit("wrong information\n");
	if ((int)ft_strlen(splited) < (int)ft_strlen(temp))
		if (ft_strchr(&temp[(int)ft_strlen(splited)], '0'))
			print_error_and_exit("wrong information\n");
	if (!is_map(splited))
		print_error_and_exit("wrong information0-1\n");
}

static void	check_middle_line(char *splited, char *temp, t_parsing_info *passing_info)
{
	int	i;

	screening_test(splited, temp);
	i = 0;
	while (splited[i])
	{
		if (i >= (int)ft_strlen(temp) && !is_space(splited[i]) && \
			splited[i] != '1') //현재 이전 줄보다 긴줄. 근데 끝에 1이나 스페이스가 아닌게 들어가 있음
				print_error_and_exit("wrong information1\n");
		if (is_space(splited[i])) //현재 줄에 스페이스가 나왔는데,
		{
			if ((!is_space(temp[i]) && temp[i] != '1')) //이전 줄이 스페이스나 1이 아님
				print_error_and_exit("wrong information2\n");
			if (i > 0 && (!is_space(splited[i - 1]) && splited[i - 1] != '1'))//현재 줄의 왼쪽이 스페이스나 1이 아님
				print_error_and_exit("wrong information3\n");
			if (i < (int)ft_strlen(splited) && \
				(splited[i + 1] && ((!is_space(splited[i + 1])) && splited[i + 1] != '1')))//현재 줄의 오른쪽이 스페이스나 1이 아님
				print_error_and_exit("wrong information4\n");
		}
		else if (splited[i] != '1' && is_space(temp[i]))
			print_error_and_exit("wrong information1\n");
		++i;
	}
	--i; // width의  \n을 빼서 저장
	if (i > passing_info->width)
		passing_info->width = i;
	++(passing_info->height);
}

void	check_valid_map(char *line, t_parsing_info *passing_info, int fd)
{
	char	*temp;
	char	*splited;

	if (!line)
		print_error_and_exit("wrong information0\n"); //Wall texture 정보만 6개 들어오고 맵 정보가 안들어온 경우
	passing_info->width = is_end_line(line) - 1; // width의  \n을 빼서 저장
	++(passing_info->height);
	temp = line;
	line = get_next_line(fd);
	splited = remove_newline(line, "\n");
	free(line);
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
