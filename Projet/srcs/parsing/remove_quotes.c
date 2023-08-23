/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:56:29 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/19 14:48:15 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

size_t	get_newcmd_len(char *cmd)
{
	size_t	i;
	size_t	counter;
	int		is_sq_opened;
	int		is_dq_opened;

	i = 0;
	counter = 0;
	is_dq_opened = -1;
	is_sq_opened = -1;
	while (cmd[i])
	{
		if (cmd[i] == '"' && is_sq_opened < 0)
			is_dq_opened *= -1;
		else if (cmd[i] == '\'' && is_dq_opened < 0)
			is_sq_opened *= -1;
		if ((cmd[i] != '"' || is_sq_opened > 0)
			&& (cmd[i] != '\'' || is_dq_opened > 0))
			counter++;
		i++;
	}
	return (counter);
}

char	*modify_cmd(char *cmd, char *new_cmd, t_garbage **gb)
{
	size_t	i;
	size_t	j;
	int		is_sq_opened;
	int		is_dq_opened;

	i = 0;
	j = 0;
	is_dq_opened = -1;
	is_sq_opened = -1;
	while (cmd[i])
	{
		if (cmd[i] == '"' && is_sq_opened < 0)
			is_dq_opened *= -1;
		else if (cmd[i] == '\'' && is_dq_opened < 0)
			is_sq_opened *= -1;
		if ((cmd[i] != '"' || is_sq_opened > 0)
			&& (cmd[i] != '\'' || is_dq_opened > 0))
			new_cmd[j++] = cmd[i];
		i++;
	}
	new_cmd[j] = 0;
	ft_free(gb, cmd);
	return (new_cmd);
}

int	delete_quotes(t_cmd_lst *cmd, t_garbage **gb)
{
	char	*new_cmd;
	size_t	new_cmd_len;

	new_cmd_len = get_newcmd_len(cmd->cmd) + 1;
	new_cmd = ft_malloc(gb, sizeof(char), new_cmd_len);
	if (!new_cmd)
		return (0);
	cmd->cmd = modify_cmd(cmd->cmd, new_cmd, gb);
	return (1);
}

int	ft_del_quotes(t_msh *msh)
{
	t_node_lst		*cmds_cpy;
	t_cmd_lst		*cmd_cpy;

	cmds_cpy = msh->lst_n;
	while (cmds_cpy)
	{
		cmd_cpy = cmds_cpy->lst_cmd;
		while (cmd_cpy)
		{
			if (!delete_quotes(cmd_cpy, &(msh->garbage)))
				return (0);
			cmd_cpy = cmd_cpy->next;
		}
		cmds_cpy = cmds_cpy->next;
	}
	return (1);
}
