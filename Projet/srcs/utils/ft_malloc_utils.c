/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:28:44 by syluiset          #+#    #+#             */
/*   Updated: 2023/10/04 17:40:16 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief
 * @param lst
 */
void	get_first_garbage(t_garbage **lst)
{
	while ((*lst)->first->prev)
		(*lst)->first = (*lst)->first->prev;
}

t_garbage	*create_garbage_container(void)
{
	t_garbage	*gb_c;

	gb_c = malloc(sizeof(t_garbage));
	if (!gb_c)
		return (NULL);
	gb_c->first = NULL;
	gb_c->last = NULL;
	return (gb_c);
}

t_garbage_lst	*new_garbage(void *content)
{
	t_garbage_lst	*new;

	new = malloc(sizeof(t_garbage_lst));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_garbage_lst	*garbage_last(t_garbage_lst *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

int	add_to_garbage(t_garbage **gb, void *content)
{
	t_garbage_lst	*new;

	new = new_garbage(content);
	if (!new)
		return (1);
	if (!(*gb)->first)
	{
		(*gb)->first = new;
		(*gb)->last = new;
	}
	else
	{
		new->prev = (*gb)->last;
		(*gb)->last->next = new;
		(*gb)->last = new;
	}
	return (0);
}
