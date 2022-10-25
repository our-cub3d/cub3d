/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehwkim <jaehwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:26:20 by jaehwkim          #+#    #+#             */
/*   Updated: 2022/10/24 14:42:38 by jaehwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../libft/libft.h"

void	check_arguments(int ac, char **av)
{
	int	i;

	if (ac != 2)
		print_error_and_exit("wrong arguments\n");
	i = ft_strlen(av[1]) - 1;
	while (av[1][i] != '.')
	{
		if (i == 0)
			print_error_and_exit("wrong file\n");
		--i;
	}
	if (ft_strncmp(av[1] + i, ".cub\0", 5) != 0)
		print_error_and_exit("wrong name\n");
}

void	check_extension_name(char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (s[i] != '.')
	{
		if (i == 0)
			print_error_and_exit("wrong file\n");
		--i;
	}
	if (ft_strncmp(s + i, ".xpm\0", 5) != 0)
		print_error_and_exit("wrong name\n");
}
