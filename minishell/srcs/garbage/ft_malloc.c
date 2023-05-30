/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:57:31 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/26 16:11:24 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

t_garbage_list	*new_garbage(void *content)
{
	t_garbage_list	*new;

	new = malloc(sizeof(t_garbage_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}


t_garbage_list	*garbage_last(t_garbage_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	garbage_add_back(t_garbage_list **lst, t_garbage_list *new)
{
	t_garbage_list	*tmp;

	if (!lst)
		return ;
	if (*lst)
	{
		tmp = garbage_last(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}

void	*ft_malloc(t_garbage **garbage, int the_size, int number)
{
	t_garbage_list	*new;
	void			*content;

	content = malloc(the_size * number);
	if (!content)
		return (NULL);
	new = new_garbage(content);
	if (!new)
		return (NULL);// ! ERROR
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