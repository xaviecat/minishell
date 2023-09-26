/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/21 16:59:30 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief execute the correct builtin in a function pointer array, and set the
 * right exit code
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 */
void	builtin_execution(t_msh *msh)
{
	static t_builtin_tab	builtin_tab[8] = {&b_echo, &b_env, &b_pwd, &b_cd,
		b_export, &b_unset, &b_exit, NULL};

	g_exit_status = builtin_tab[msh->lst_n->builtin](msh);
}

/**
 * @brief choose if minishell need to fork or execute the command and the
 * builtins in the current process
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 */
void	execution(t_msh *msh)
{
	if ((msh->n_node >= 1 && (msh->lst_n->builtin < e_cd
				|| msh->lst_n->builtin == e_none)) || msh->n_node > 1)
		forking(msh);
	else if (msh->n_node == 1 && msh->lst_n->builtin >= e_cd)
		builtin_execution(msh);
}
