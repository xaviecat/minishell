/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_in_minish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:50:54 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/14 14:58:55 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_error_cmd_w(t_garbage **gb, t_w_cmd_list **lst)
{
	t_w_cmd_list	*next;

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

void	free_error_cmd(t_garbage **gb, t_cmd_list **lst)
{
	t_cmd_list	*next;

	next = NULL;
	while (*lst)
	{
		if ((*lst)->next)
			next = (*lst)->next;
		else
			next = NULL;
		free_error_redir(gb, &((*lst)->redirs));
		free_error_fds(gb, &((*lst)->fds));
		free_error_cmd_w(gb, &((*lst)->cmd));
		*lst = next;
	}
}

t_cmd_list	*create_command(t_minish **sh)
{
	t_redir_list	*redirs;
	t_fd_list		*fds;
	t_cmd_list		*new;

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
int	sh_pars(t_minish **sh)
{
	t_cmd_list		*new;

	new = NULL;
	if (!(*sh)->lst_w)
		return (0);
	while ((*sh)->lst_w)
	{
		new = create_command(sh);
		if (!new && errno == ENOMEM)
			return (free_error_cmd(&((*sh)->garbage), &((*sh)->cmds)), 0);
		if (new->cmd)
			new->builtin = builtin_or_command(new->cmd->cmd);
		if ((*sh)->cmds)
		{
			new->previous = (*sh)->cmds->last_added;
			(*sh)->cmds->last_added->next = new;
		}
		else
			(*sh)->cmds = new;
		(*sh)->cmds->last_added = new;
		if ((*sh)->lst_w && (*sh)->lst_w->type == w_pipe)
			word_lst_delone(&(*sh)->lst_w, &(*sh)->garbage);
	}
	return (1);
}
