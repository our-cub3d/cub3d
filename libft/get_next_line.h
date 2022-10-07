/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:25:11 by hogkim            #+#    #+#             */
/*   Updated: 2022/07/11 18:34:48 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"

# define BUFFER_SIZE 50000

char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_no_newline(char *buffer);
char	*ft_strjoin_gnl(char *s1, char *s2);

char	*ft_restart(char *temp);
char	*ft_cut_temp(char *temp);
char	*ft_read_till_line(int fd, char *temp);
char	*get_next_line(int fd);

#endif
