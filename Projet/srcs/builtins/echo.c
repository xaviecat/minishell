/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:08:46 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/21 21:33:05 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Checking if we should display a '\n' at the end of the echo
 * @param lst
 * @return true if we should display, false in other case
 */
bool	is_n_param(t_cmd_lst *lst)
{
	int	i;

	i = 1;
	if (!lst || !lst->cmd)
		return (false);
	if (lst->cmd[0] != '-')
		return (false);
	if (lst->cmd[i] == '\0')
		return (false);
	while (lst->cmd[i])
	{
		if (lst->cmd[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	b_echo(t_msh *msh)
{
	bool	new_line;

	new_line = true;
	if (!msh->lst_n->lst_cmd->next)
		return (printf("\n"), 0);
	msh->lst_n->lst_cmd = msh->lst_n->lst_cmd->next;
	while (is_n_param(msh->lst_n->lst_cmd))
	{
		new_line = false;
		msh->lst_n->lst_cmd = msh->lst_n->lst_cmd->next;
	}
	while (msh->lst_n->lst_cmd)
	{
		if (msh->lst_n->lst_cmd->next)
			printf("%s ", msh->lst_n->lst_cmd->cmd);
		else
			printf("%s", msh->lst_n->lst_cmd->cmd);
		msh->lst_n->lst_cmd = msh->lst_n->lst_cmd->next;
	}
	if (new_line)
		printf("\n");
	return (0);
}
