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

/**
 * @brief create a new node of redir_list
 * @param gb
 * @param lst
 * @return the new node with the type of redirection
 */
t_redir_lst	*create_redir(t_garbage **gb, t_word_lst *lst)
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

/**
 * @brief Create a list of redirection, get and stock the filename
 * after redirection
 * @param lst
 * @param gb
 * @return a list of the type of the redirection and the filename
 */
t_redir_lst	*get_redir(t_word_lst **lst, t_garbage **gb)
{
	t_redir_lst	*redirs;
	t_redir_lst	*new;

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
