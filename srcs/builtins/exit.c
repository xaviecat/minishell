/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:05:10 by syluiset          #+#    #+#             */
/*   Updated: 2023/10/09 13:59:10 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Exit the minishell and give the number (if there is one) to
 * the exit status
 * @param msh
 * @return 2 or 1 if there is an error
 */
int	b_exit(t_msh *msh)
{
	unsigned int	ret;

	ret = 0;
	if (msh->lst_n->lst_cmd->next
		&& !(ft_atoi_custom(msh->lst_n->lst_cmd->next->cmd, &ret)))
	{
		ret = 2;
		return (free_and_exit_minish(msh, NULL, ret), ret);
	}
	if (msh->lst_n->lst_cmd->next && msh->lst_n->lst_cmd->next->next)
	{
		ft_fdprintf(1, "exit\n");
		return (ft_fdprintf(2, MSH E_EXIT TOO_MN_ARGS), 1);
	}
	if (msh->lst_n->lst_cmd->next)
	{
		if (!(ft_atoi_custom(msh->lst_n->lst_cmd->next->cmd, &ret)))
			g_exit_status = 2;
		else
			g_exit_status = ret;
	}
	if (msh->lst_n->pid < 0)
		ft_fdprintf(1, "exit\n");
	return (free_and_exit_minish(msh, NULL, g_exit_status), g_exit_status);
}
