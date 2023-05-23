/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:57:31 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/23 14:27:04 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_garbage_list	*new_garbage(void *content)
{
	t_garbage_list	*new;

	new = malloc(sizeof(t_garbage_list));
	new->content = content;
	new->next = NULL;
	return (new);
}

void	garbage_lst_delone(t_garbage_list **lst)
{
	t_garbage_list	*prev;

	prev =
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

void	*ft_malloc(t_garbage_list **garbage, int the_size, int number)
{
	t_garbage_list	*new;
	void			*content;

	content = malloc(the_size * number);
	if (!content)
		return (NULL);
	new = new_garbage(content);
	garbage_add_back(garbage, new);
	return (content);
}
