/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehwkim <jaehwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:26:18 by jaehwkim          #+#    #+#             */
/*   Updated: 2022/10/25 14:16:11 by jaehwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../libft/libft.h"

static void	screening_test(char *splited, char *temp)
{
	if (splited[0] == '0' || splited[ft_strlen(splited) - 1] == '0')
		print_error_and_exit("wrong information1\n");
	if ((int)ft_strlen(splited) < (int)ft_strlen(temp))
		if (ft_strchr(&temp[(int)ft_strlen(splited)], '0'))
			print_error_and_exit("wrong information2\n");
	if (!is_map(splited))
		print_error_and_exit("wrong information3\n");
}

#include <stdio.h>

static void	check_valid_wall(char *splited, char *temp, int i)
{
	if (is_space(splited[i]))
	{
		if ((int)ft_strlen(temp) > i && (!is_space(temp[i]) && temp[i] != '1'))
		{
			printf("temp : |%c|\n splited : |%c|\n i :|%d| \n", temp[i], splited[i], i);
			print_error_and_exit("wrong information4\n");
		}
		if (i > 0 && (!is_space(splited[i - 1]) && splited[i - 1] != '1'))
			print_error_and_exit("wrong information5\n");
		if (i < (int)ft_strlen(splited) && \
			(splited[i + 1] && ((!is_space(splited[i + 1])) \
			&& splited[i + 1] != '1')))
			print_error_and_exit("wrong information6\n");
	}
	else if (splited[i] != '1' && is_space(temp[i]))
		print_error_and_exit("wrong information7\n");
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
			print_error_and_exit("wrong information8\n");
		check_valid_wall(splited, temp, i);
		++i;
	}
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
		if (!line)
		{
			is_end_line(temp);
			free(temp);
			break ;
		}
		if (line[0] == '\n')
		{
			is_end_line(temp);
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
		print_error_and_exit("wrong information9\n");
	passing_info->width = is_end_line(line);
	++(passing_info->height);
	temp = line;
	line = get_next_line(fd);
	if (!line)
		print_error_and_exit("wrong information10\n");
	splited = remove_newline(line, "\n");
	if (splited == NULL)
	{
		free(splited);
		splited = ft_strdup(" ");
	}
	free(line);
	check_all_line(splited, temp, passing_info, fd);
}
