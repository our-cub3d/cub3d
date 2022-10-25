/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehwkim <jaehwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:57:46 by jaehwkim          #+#    #+#             */
/*   Updated: 2022/10/25 10:40:10 by jaehwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_restart(char *temp)
{
	size_t	i;
	size_t	len;
	char	*str;

	len = ft_strlen(temp);
	i = 0;
	while (temp[i] && (temp[i] != '\n'))
		i++;
	if (!temp[i])
	{
		free(temp);
		return (NULL);
	}
	str = (char *)calloc((len - i), sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &temp[i + 1], len - i);
	free(temp);
	return (str);
}

char	*ft_cut_temp(char *temp)
{
	size_t	i;
	char	*line;

	if (!temp[0])
		return (NULL);
	i = 0;
	while ((temp[i] != '\n') && temp[i])
		i++;
	line = (char *)calloc((i + 2), sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, temp, i + 2);
	return (line);
}

char	*ft_read_till_line(int fd, char *temp)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	n;

	n = 1;
	while (n && ft_no_newline(temp))
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
			return (NULL);
		buffer[n] = 0;
		temp = ft_strjoin_gnl(temp, buffer);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp[512];
	char		*line;

	if (fd < 0 || fd > 511 || BUFFER_SIZE <= 0)
		return (NULL);
	temp[fd] = ft_read_till_line(fd, temp[fd]);
	if (!temp[fd])
		return (NULL);
	line = ft_cut_temp(temp[fd]);
	temp[fd] = ft_restart(temp[fd]);
	return (line);
}
