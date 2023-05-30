/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:17:09 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/30 14:51:00 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_free(t_garbage **lst, void *content)
{
	t_garbage_list	*first;
	t_garbage_list	*prev;
	t_garbage_list	*next;

	prev = NULL;
	next = NULL;
	if (content == (*lst)->first->content)
	{
		first = (*lst)->first->next;
		if (first)
			first->prev = NULL;
		free((*lst)->first->content);
		free((*lst)->first);
	}
	else
	{
		first = (*lst)->first;
		while ((*lst)->first && (*lst)->first->content != content)
		{
			if ((*lst)->first->next && (*lst)->first->next->content == content)
			{
				prev = (*lst)->first;
				(*lst)->first = (*lst)->first->next;
				next = (*lst)->first->next;
				free((*lst)->first->content);
				free((*lst)->first);
				if (next)
					next->prev = prev;
				if (prev)
					prev->next = next;
				break ;
			}
			(*lst)->first = (*lst)->first->next;
		}
	}
	(*lst)->first = first;
}

void    ft_free_all(t_garbage **lst)
{
	t_garbage_list	*next;

	next = NULL;
	while ((*lst)->first)
	{
		if ((*lst)->first->next)
			next = (*lst)->first->next;
		else
			next = NULL;
		free((*lst)->first->content);
		free((*lst)->first);
		if (next)
			next->prev = NULL;
		(*lst)->first = next;
	}
}