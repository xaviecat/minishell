/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:50:32 by xcharra           #+#    #+#             */
/*   Updated: 2022/11/16 12:57:09 by xcharra          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*tmpnxt;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp != NULL)
	{
		tmpnxt = tmp;
		tmp = tmp->next;
		ft_lstdelone(tmpnxt, (del));
	}
	*lst = NULL;
	return ;
}
