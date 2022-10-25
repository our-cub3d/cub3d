/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_wall_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehwkim <jaehwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:26:54 by jaehwkim          #+#    #+#             */
/*   Updated: 2022/10/25 10:53:45 by jaehwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

static void	update_value(char **info, char *value)
{
	if (*info)
		print_error_and_exit("wrong information\n");
	check_extension_name(value);
	*info = value;
}

static int	compare_and_save(char **splited, t_cube_info *cube_info)
{
	if (!ft_strncmp(splited[0], "NO", 3))
		update_value(&cube_info->no, splited[1]);
	else if (!ft_strncmp(splited[0], "SO", 3))
		update_value(&cube_info->so, splited[1]);
	else if (!ft_strncmp(splited[0], "WE", 3))
		update_value(&cube_info->we, splited[1]);
	else if (!ft_strncmp(splited[0], "EA", 3))
		update_value(&cube_info->ea, splited[1]);
	else
	{
		free(splited[0]);
		free(splited[1]);
		return (0);
	}
	free(splited[0]);
	return (1);
}

static void	fc_update_value(long long *info, long long value)
{
	if (*info != -1)
		print_error_and_exit("wrong information\n");
	*info = value;
}

static int	fc_compare_and_save(char **splited, t_cube_info *cube_info)
{
	long long	result;
	long long	value;
	int			i;

	result = 0;
	i = 1;
	while (i < 4)
	{
		value = ft_atoi(splited[i]);
		if (value > 255)
			print_error_and_exit("wrong information\n");
		result += value;
		if (i != 3)
			result = result << 8;
		++i;
	}
	if (!ft_strncmp(splited[0], "F", 2))
		fc_update_value(&cube_info->f, result);
	else if (!ft_strncmp(splited[0], "C", 2))
		fc_update_value(&cube_info->c, result);
	i = 0;
	while (i < 4)
		free(splited[i++]);
	return (1);
}

int	read_wall_texture(char *line, t_game *game)
{
	static char	spaces[7] = {'\t', '\n', '\v', '\f', '\r', ' ', 0};
	char		**splited;
	int			result;

	if (ft_word_count(line, spaces) == 0)
		return (-1);
	if (get_fc(line))
	{
		splited = ft_split(line, ", \t\v\n\f\r");
		result = fc_compare_and_save(splited, game->cube_info);
	}
	else
	{
		if (ft_word_count(line, spaces) != 2)
			return (0);
		splited = ft_split(line, spaces);
		result = compare_and_save(splited, game->cube_info);
	}
	free(splited);
	return (result);
}
