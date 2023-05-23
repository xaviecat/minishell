/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_in_minish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:50:54 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/22 13:53:58 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief parsing redirection list, command list, fd list in minishell struct
 * @param old_lst
 * @param minish
 */
void	sh_pars(t_word_lst **old_lst, t_minish **minish)
{
	t_redir_list	*redirs;
	t_fd_list		*fds;
	t_cmd_list		*new;

	redirs = NULL;
	fds = NULL;
	new = NULL;
	while (*old_lst)
	{
		redirs = get_redir(old_lst);
		fds = create_fds_list(redirs);
		new = lst_cmd_new(get_cmd_2(old_lst), fds, redirs);
		new->builtin = builtin_or_command(new->cmd->cmd);
		lst_cmd_add_back(&(*minish)->cmds, new);
		if (*old_lst && (*old_lst)->type == w_pipe)
			word_lst_delone(old_lst);
	}
}