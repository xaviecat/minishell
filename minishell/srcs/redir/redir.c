/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:21:43 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/14 14:18:32 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_redir_list	*create_redir(t_garbage **gb, t_word_lst *lst)
{
	if (lst->type == open_file)
		return (new_redir(in, gb));
	if (lst->type == hd)
		return (new_redir(inin, gb));
	if (lst->type == redir)
		return (new_redir(out, gb));
	if (lst->type == appnd)
		return (new_redir(outout, gb));
	return (NULL);
}

t_redir_list	*get_redir(t_word_lst **lst, t_garbage **gb)
{
	t_redir_list	*redirs;
	t_redir_list	*new;

	redirs = NULL;
	new = NULL;
	while (*lst && (*lst)->type != w_pipe)
	{
		new = create_redir(gb, *lst);
		if (new)
		{
			word_lst_delone(lst, gb);
			new->filename = ft_gbstrdup((*lst)->word, gb);
			word_lst_delone(lst, gb);
			redir_add_back(&redirs, new);
		}
		else
		{
			if (errno == ENOMEM)
				return (free_error_redir(gb, &redirs), NULL);
			if (!(*lst)->next)
				break ;
			*lst = (*lst)->next;
		}
	}
	return (*lst = word_lst_first(*lst), redirs);
}
