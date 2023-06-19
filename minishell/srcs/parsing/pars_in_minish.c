/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_in_minish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:50:54 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/15 17:18:26 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_error_cmd_w(t_garbage **gb, t_cmd_lst **lst)
{
	t_cmd_lst	*next;

	next = NULL;
	while (*lst)
	{
		if ((*lst)->next)
			next = (*lst)->next;
		else
			next = NULL;
		ft_free(gb, (*lst)->cmd);
		ft_free(gb, *lst);
		*lst = next;
	}
}

void	free_error_cmd(t_garbage **gb, t_node_lst **lst)
{
	t_node_lst	*next;

	next = NULL;
	while (*lst)
	{
		if ((*lst)->next)
			next = (*lst)->next;
		else
			next = NULL;
		free_error_redir(gb, &((*lst)->redirs));
		free_error_fds(gb, &((*lst)->fds));
		free_error_cmd_w(gb, &((*lst)->lst_cmd));
		*lst = next;
	}
}

t_node_lst	*create_command(t_msh **sh)
{
	t_redir_lst	*redirs;
	t_fd_lst		*fds;
	t_node_lst		*new;

	redirs = get_redir(&((*sh)->lst_w), &((*sh)->garbage));
	if (errno == ENOMEM)
		return (free_error_word_lst(&((*sh)->garbage), &((*sh)->lst_w)), NULL);
	fds = create_fds_list(redirs, &(*sh)->garbage);
	if (errno == ENOMEM)
		return (free_error_word_lst(&((*sh)->garbage), &((*sh)->lst_w)), NULL);
	new = lst_cmd_new(get_cmd(&(*sh)->lst_w, &(*sh)->garbage),
			fds, redirs, &((*sh)->garbage));
	return (new);
}

/**
 * @brief parsing redirection list, command list, fd list in minishell struct
 * @param old_lst
 * @param minish
 */
int	sh_pars(t_msh **msh)
{
	t_node_lst		*new;

	new = NULL;
	if (!(*msh)->lst_w)
		return (0);
	while ((*msh)->lst_w)
	{
		new = create_command(msh);
		if (!new && errno == ENOMEM)
			return (free_error_cmd(&((*msh)->garbage), &((*msh)->lst_n)), 0);
		if (new->lst_cmd)
			new->builtin = builtin_or_command(new->lst_cmd->cmd);
		if ((*msh)->lst_n)
		{
			new->previous = (*msh)->lst_n->last_added;
			(*msh)->lst_n->last_added->next = new;
		}
		else
			(*msh)->lst_n = new;
		(*msh)->lst_n->last_added = new;
		if ((*msh)->lst_w && (*msh)->lst_w->type == w_pipe)
			word_lst_delone(&(*msh)->lst_w, &(*msh)->garbage);
	}
	return (1);
}
