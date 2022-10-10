#include "../include/cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

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

	if (ft_word_count(line, spaces) == 0)
		return (-1);
	if (ft_word_count(line, spaces) != 2)
		return (0);
	splited = ft_split(line, spaces);
	result = compare_and_save(splited, game->cube_info);
	free(splited);
	return (result);
}

int	is_space(char	c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_map(char	*line)
{
	int	len;

	len = 0;
	while (line[len])
	{
		if (line[len] != '0' && line[len] != '1' && !is_space(line[len]))
			return (0);
		++len;
	}
	return (1);
}

int	is_end_line(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		// printf("i : %d, char : |%c|\n", i, line[i]);
		if (line[i] != '1' && !is_space(line[i]))
			print_error_and_exit("wrong information6\n"); //첫줄에 1이나 spaces가 아닌 문자
		++i;
	}
	return (i);
}

void	check_valid_map(char *line, t_parsing_info *passing_info, int fd)
{
	char	*temp;
	char	*splited;
	int		i;

	if (!line)
		print_error_and_exit("wrong information0\n"); //Wall texture 정보만 6개 들어오고 맵 정보가 안들어온 경우
	passing_info->width = is_end_line(line);
	++(passing_info->height);
	temp = line;
	line = get_next_line(fd);
	splited = *ft_split(line, "\n");
	free(line);
	while (splited)
	{
		i = 0;
		printf("|%s|\n", splited);
		while (splited[i])
		{
			if (i > (int)ft_strlen(temp) && !is_space(splited[i]) && \
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
			++i;
		}
		if (i > passing_info->width)
			passing_info->width = i;
		++(passing_info->height);
		free(temp);
		temp = splited;
		splited = NULL;
		line = get_next_line(fd);
		if (!line)
		{
			is_end_line(temp);
			break ;
		}
		splited = *ft_split(line, "\n");
		free(line);
	}
}

void	read_map(char *name_of_map, t_game *game)
{
	char		*line;
	int			fd;

	fd = open(name_of_map, O_RDONLY);// open 해서 유효성 검사
	line = get_next_line(fd);
	while (line)
	{
		if (read_wall_texture(line, game) == 0)
		{
			if (!is_map(line) || count_null_in_cube_info(game->cube_info) != 6)
				print_error_and_exit("wrong information\n");
			else
				break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	print_cube_info(game->cube_info);
	// printf("!!!!!!\n");
	check_valid_map(line, game->parsing_info, fd); //맵의 유효성 검사. 양 끝단, 스페이스 전 좌우 비교
	//fd = open(name_of_map, O_RDONLY);// malloc 해서 파싱
}
