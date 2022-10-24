/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surlee <surlee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 23:26:06 by hogkim            #+#    #+#             */
/*   Updated: 2022/10/24 14:07:54 by surlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (src[i])
		i++;
	if (dstsize == 0)
		return (i);
	j = 0;
	while (j < dstsize - 1 && j < i)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = 0;
	return (i);
}

int	ft_no_newline(char *s)
{
	size_t	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcpy(&str[ft_strlen(s1)], s2, ft_strlen(s2) + 1);
	free(s1);
	return (str);
}
