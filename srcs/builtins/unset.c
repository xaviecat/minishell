/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:43:43 by syluiset          #+#    #+#             */
/*   Updated: 2023/10/05 15:57:34 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/***
 * @brief reallocates an modify env without variables to be deleted
 * @return 0 on success \n ENOMEM if allocation failed
 */
static int	unset_name_var(t_msh *sh)
{
	char	**old_envp;
	char	*name_var;

	name_var = ft_gbstrdup(sh->lst_n->lst_cmd->cmd, &(sh->garbage));
	check_var_exist(name_var, sh->envp);
	old_envp = ft_gbtabdup(sh->envp, &(sh->garbage));
	if (!old_envp && errno == ENOMEM)
		return (ENOMEM);
	ft_gbtabfree(sh->envp, &(sh->garbage));
	sh->envp = ft_malloc(&(sh->garbage), sizeof(char *),
			length_c_tab(old_envp) + 1);
	if (!sh->envp)
		free_and_exit_minish(sh, NULL, EXIT_FAILURE);
	unset_tab(sh->envp, old_envp, &(sh->garbage), name_var);
	ft_free(&(sh->garbage), name_var);
	return (0);
}

/***
 * @brief unsets environment variables by deleting them from env
 * @return the corresponding exit status
 */
int	b_unset(t_msh *sh)
{
	int		ret_error;

	if (!sh->lst_n->lst_cmd->next)
		return (0);
	sh->lst_n->lst_cmd = sh->lst_n->lst_cmd->next;
	ret_error = string_is_valid(sh->lst_n->lst_cmd);
	if (ret_error > 0)
		return (ret_error);
	while (sh->lst_n->lst_cmd)
	{
		if (unset_name_var(sh) != 0)
			return (ENOMEM);
		sh->lst_n->lst_cmd = sh->lst_n->lst_cmd->next;
	}
	return (0);
}
