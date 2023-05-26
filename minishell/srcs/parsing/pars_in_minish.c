/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_in_minish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:50:54 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/26 15:46:20 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief parsing redirection list, command list, fd list in minishell struct
 * @param old_lst
 * @param minish
 */
void	sh_pars(t_minish **sh)
{
	t_redir_list	*redirs;
	t_fd_list		*fds;
	t_cmd_list		*new;

	redirs = NULL;
	fds = NULL;
	new = NULL;
	while ((*sh)->lst_w)
	{
		redirs = get_redir(&(*sh)->lst_w, &(*sh)->garbage);
		fds = create_fds_list(redirs, &(*sh)->garbage);
		new = lst_cmd_new(get_cmd_2(&(*sh)->lst_w, &(*sh)->garbage), fds, redirs, &((*sh)->garbage));
		new->builtin = builtin_or_command(new->cmd->cmd);
		if ((*sh)->cmds)
		{
			new->previous = (*sh)->cmds->last_added;
			(*sh)->cmds->last_added->next = new;
		}
		else
			(*sh)->cmds = new;
		(*sh)->cmds->last_added = new;
		//lst_cmd_add_back(&(*minish)->cmds, new);
		if ((*sh)->lst_w && (*sh)->lst_w->type == w_pipe)
			word_lst_delone(&(*sh)->lst_w, &(*sh)->garbage);
	}
}