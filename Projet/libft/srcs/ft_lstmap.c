/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:22:23 by xcharra           #+#    #+#             */
/*   Updated: 2022/11/15 12:39:22 by xcharra          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*newnxt;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (ft_lstclear(&new, del), NULL);
	lst = lst->next;
	while (lst)
	{
		newnxt = ft_lstnew(f(lst->content));
		if (!newnxt)
		{
			ft_lstclear(&newnxt, del);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, newnxt);
		lst = lst->next;
	}
	return (new);
}
