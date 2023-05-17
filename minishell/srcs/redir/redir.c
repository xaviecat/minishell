/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:21:43 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/17 18:36:35 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_redir_list	*new_redir(t_type_redir type_red)
{
	t_redir_list	*red;

	red = malloc(sizeof(t_redir_list));
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

t_redir_list	*get_redir(t_word_lst **lst)
{
	t_redir_list	*redirs;
	t_redir_list	*new;

	redirs = NULL;
	new = NULL;
	while (*lst && (*lst)->type != w_pipe)
	{
		if ((*lst)->type == open_file)
			new = new_redir(in);
		if ((*lst)->type == hd)
			new = new_redir(inin);
		if ((*lst)->type == redir)
			new = new_redir(out);
		if ((*lst)->type == appnd)
			new = new_redir(outout);
		if (new)
		{
			word_lst_delone(lst);
			new->filename = ft_strdup((*lst)->word);
			word_lst_delone(lst);
			redir_add_back(&redirs, new);
		}
		*lst = (*lst)->next;
	}
	*lst = word_lst_first(*lst);
	return (redirs);
}