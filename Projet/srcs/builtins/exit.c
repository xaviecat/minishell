/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:05:10 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/18 17:50:55 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	b_exit(t_msh *msh)
{
	int	ret;

	ret = 0;
	if (!(ft_atoi_custom(msh->lst_n->lst_cmd->next->cmd, &ret)))
		return (ft_fdprintf(2, RED MSH E_EXIT NUM_ARG RESET), 2);
	if (msh->lst_n->lst_cmd->next && msh->lst_n->lst_cmd->next->next)
		return (ft_fdprintf(2, RED MSH E_EXIT TOO_MN_ARGS RESET), 1);
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
