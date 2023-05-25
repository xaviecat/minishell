/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:17:09 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/23 16:12:35 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_free(t_garbage_list **lst, void *content)
{
	t_garbage_list	*first;
	t_garbage_list	*prev;
	t_garbage_list	*next;

    dprintf(2,"%p", content);
	if (content == (*lst)->content)
	{
		first = (*lst)->next;
		free((*lst)->content);
		free(*lst);
	}
	else
	{
		first = *lst;
        while ((*lst)->content != content)
        {
            if ((*lst)->next->content == content)
            {
                prev = *lst;
                *lst = (*lst)->next;
                next = (*lst)->next;
                free((*lst)->content);
                free(*lst);
                prev->next = next;
                break ;
            }
            *lst = (*lst)->next;
        }
	}
	*lst = first;
}

void    ft_free_all(t_garbage_list *lst)
{
    t_garbage_list  *next;

    while (lst)
    {
        next = lst->next;
        free(lst->content);
        free(lst);
        lst = next;
    }
}