/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:18:34 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/14 14:21:20 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_redir_list	*new_redir(t_type_redir type_red, t_garbage **gb)
{
	t_redir_list	*red;

	red = ft_malloc(gb, sizeof(t_redir_list), 1);
	if (!red)
		return (NULL);
	red->redir = type_red;
	red->next = NULL;
	return (red);
}

t_redir_list	*redir_last(t_redir_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	redir_add_back(t_redir_list **lst, t_redir_list *new)
{
	t_redir_list	*tmp;

	if (!lst)
		return ;
	if (*lst)
	{
		tmp = redir_last(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}

void	free_error_redir(t_garbage **gb, t_redir_list **lst)
{
	t_redir_list	*next;

	next = NULL;
	while (*lst)
	{
		if ((*lst)->next)
			next = (*lst)->next;
		else
			next = NULL;
		ft_free(gb, *lst);
		*lst = next;
	}
}
