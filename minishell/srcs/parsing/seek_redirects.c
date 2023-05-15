/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:09:22 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/11 19:07:07 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h'
#include "../../incs/minishell.h"

void	get_redir_type(t_cmd_list *cmdlst);

void	seek_redirection(t_minish *mnsh)
{
	t_cmd_list	*cmdlst;
	cmdlst = mnsh->cmd;
	while(cmdlst)
	{
		get_redir_type(cmdlst);
		cmdlst = cmdlst->next;
	}
}

void	get_redir_type(t_cmd_list *cmdlst)
{
	int	i;

	i = 0;
	while(cmdlst->cmd[0][i])
	{
		if (cmdlst->cmd[0][i] && cmdlst->cmd[0][i] != '<')
			i++;
		if (cmdlst->cmd[0][i] && cmdlst->cmd[0][i] == '<')
		{
			if (cmdlst->cmd[0][i + 1] && cmdlst->cmd[0][i + 1] == '<')
				//go heredoc LIMIT; >
			else if (cmdlst->cmd[0][i + 1] && cmdlst->cmd[0][i + 1] != '<')
				// open file name;
			i++;
		}
	}
}


/*
 * get <
 * count <
 * get infile
 * if < open(infile, O_RDONLY, 0444);
 * if << heredoc
 * if other redirect close prev and redo
 *
 *
 * get >
 * count >
 * get filename
 * if > open(oufile, O_RDWR | O_CREAT | O_TRUNC, 0644);
 * if >> open(oufile, O_RDWR | O_CREAT | O_APPEND, 0644);
 * if other redirect close prev and redo
 *
 * */