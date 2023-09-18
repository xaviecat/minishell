/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:08:46 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/29 11:32:24 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

//static bool	param_n(t_cmd_lst *lst)
//{
//	int			i;
//	bool		ret;
//
//	ret = false;
//	while (lst)
//	{
//		if (lst->cmd[0] != '-')
//			return (ret);
//		i = 1;
//		while (lst->cmd[i] && lst->cmd[i] == 'n')
//		{
//			ret = true;
//			i++;
//			if (lst->cmd[i] != '\0' && lst->cmd[i] != 'n')
//				return (false);
//		}
//		lst = lst->next;
//	}
//	return (ret);
//}
//
//int	b_echo(t_msh *msh)
//{
//	bool	new_line;
//
	//if (!msh->lst_n->lst_cmd)
	//	return (1);
//	if (msh->lst_n->lst_cmd->next)
//		msh->lst_n->lst_cmd = msh->lst_n->lst_cmd->next;
//	while ()
//	new_line = param_n(msh->lst_n->lst_cmd);
//	while (msh->lst_n->lst_cmd)
//	{
//		if (msh->lst_n->lst_cmd->next)
//			printf("%s ", msh->lst_n->lst_cmd->cmd);
//		else
//			printf("%s", msh->lst_n->lst_cmd->cmd);
//		msh->lst_n->lst_cmd = msh->lst_n->lst_cmd->next;
//	}
//	if (!new_line)
//		printf("\n");
//	return (0);
//}

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
