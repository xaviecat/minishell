/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:05:10 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/26 15:54:42 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

//static int	verif_arg_exit(t_msh *msh)
//{
//	int	i;
//
//	i = 0;
//	if (msh->lst_n->lst_cmd && msh->lst_n->lst_cmd->next)
//	{
//		if (msh->lst_n->lst_cmd->next->cmd)
//		{
//			while (msh->lst_n->lst_cmd->next->cmd[i])
//			{
//				if (ft_isalpha(msh->lst_n->lst_cmd->next->cmd[i]))
//				{
//					g_exit_status = 2;
//					dprintf(2, "minishell: exit: %s: numeric argument required",
//						msh->lst_n->lst_cmd->next->cmd);
//					return (0);
//				}
//				i++;
//			}
//			return (1);
//		}
//	}
//	return (0);
//}


int	b_exit(t_msh *msh)
{
	int	ret;

	ret = 0;
	if (msh->lst_n->lst_cmd->next && msh->lst_n->lst_cmd->next->next)
		return (ft_putendl_fd("minishell: exit: too many arguments", 2), 1);
	if (msh->lst_n->lst_cmd->next)
	{
		if (!(ft_atoi_custom(msh->lst_n->lst_cmd->next->cmd, &ret)))
			g_exit_status = 2;
		else
			g_exit_status = ret;
	}
	ft_free_all(&(msh->garbage));
	free(msh->garbage);
	msh->garbage = NULL;
	free(msh);
	msh = NULL;
	exit(g_exit_status);
}
