/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehwkim <jaehwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:26:50 by jaehwkim          #+#    #+#             */
/*   Updated: 2022/10/24 14:26:57 by jaehwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_space(char c)
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
		if (line[len] != '0' && line[len] != '1' && !is_space(line[len]) \
			&& line[len] != 'N' && line[len] != 'S' && line[len] != 'E' \
			&& line[len] != 'W')
			return (0);
		++len;
	}
	return (1);
}

int	is_end_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && !is_space(line[i]))
			print_error_and_exit("wrong information\n");
		++i;
	}
	return (i);
}
