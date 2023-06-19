/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:08:46 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/19 14:58:59 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static bool	param_n(t_cmd_lst **lst)
{
	t_cmd_lst	*first;
	int			i;
	bool		ret;

	ret = false;
	first = *lst;
	while (*lst)
	{
		if ((*lst)->cmd[0] != '-')
			return (ret);
		i = 1;
		while ((*lst)->cmd[i] && (*lst)->cmd[i] == 'n')
		{
			ret = true;
			i++;
			if ((*lst)->cmd[i] != '\0' && (*lst)->cmd[i] != 'n')
			{
				*lst = first;
				return (false);
			}
		}
		*lst = (*lst)->next;
	}
	return (ret);
}

int	b_echo(t_msh *msh)
{
	bool	new_line;

	if (!msh->lst_n->lst_cmd)
		return (1);
	msh->lst_n->lst_cmd = msh->lst_n->lst_cmd->next;
	new_line = param_n(&(msh->lst_n->lst_cmd));
	while (msh->lst_n->lst_cmd)
	{
		if (msh->lst_n->lst_cmd->next)
			printf("%s ", msh->lst_n->lst_cmd->cmd);
		else
			printf("%s", msh->lst_n->lst_cmd->cmd);
		msh->lst_n->lst_cmd = msh->lst_n->lst_cmd->next;
	}
	if (!new_line)
		printf("\n");
	return (0);
}
