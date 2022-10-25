/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehwkim <jaehwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 23:47:53 by surlee            #+#    #+#             */
/*   Updated: 2022/10/25 10:42:19 by jaehwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;

	if (!(*lst))
		return ;
	p = *lst;
	while (p)
	{
		*lst = (*lst)->next;
		ft_lstdelone(p, del);
		p = *lst;
	}
}
