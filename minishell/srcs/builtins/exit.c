/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:05:10 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/20 13:08:41 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	verif_arg_exit(t_msh *msh)
{
	int	i;

	i = 0;
	if (msh->lst_n->lst_cmd && msh->lst_n->lst_cmd->next)
	{
		if (msh->lst_n->lst_cmd->next->cmd)
		{
			while (msh->lst_n->lst_cmd->next->cmd[i])
			{
				if (ft_isalpha(msh->lst_n->lst_cmd->next->cmd[i]))
				{
					g_exit_status = 2;
					printf("exit: %s: numeric argument required",
						msh->lst_n->lst_cmd->next->cmd);
					return (0);
				}
				i++;
			}
			return (1);
		}
	}
	return (0);
}

int	b_exit(t_msh *msh)
{
	if (verif_arg_exit(msh))
		g_exit_status = ft_atoi(msh->lst_n->lst_cmd->next->cmd);
	ft_free_all(&(msh->garbage));
	free(msh->garbage);
	msh->garbage = NULL;
	free(msh);
	msh = NULL;
	exit(EXIT_SUCCESS);// ! a changer
}
