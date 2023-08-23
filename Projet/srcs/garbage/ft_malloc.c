/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:57:31 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/12 17:07:31 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

void	add_to_garbage(t_garbage **gb, void *content)
{
	t_garbage_lst	*new;

	new = new_garbage(content);
	(*gb)->last->next = new;
	(*gb)->last = new;
}

void	*ft_malloc(t_garbage **garbage, int the_size, int number)
{
	t_garbage_lst	*new;
	void			*content;

	new = NULL;
	content = NULL;
	content = malloc(the_size * number);
	if (!content)
		return (NULL);
	new = new_garbage(content);
	if (!new)
		return (NULL);
	if (!(*garbage)->first)
	{
		(*garbage)->first = new;
		(*garbage)->last = new;
	}
	else
	{
		new->prev = (*garbage)->last;
		(*garbage)->last->next = new;
		(*garbage)->last = new;
	}
	return (content);
}
