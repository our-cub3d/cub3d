/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utills.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehwkim <jaehwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:26:23 by jaehwkim          #+#    #+#             */
/*   Updated: 2022/10/25 11:16:35 by jaehwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../libft/libft.h"

char	*remove_newline(char *line, char *set)
{
	char	**splited;
	char	*tmp;

	splited = ft_split(line, set);
	if (splited[0] == NULL)
	{
		free(splited);
		return (ft_strdup(" "));
	}
	tmp = splited[0];
	free(splited[1]);
	free(splited);
	return (tmp);
}
