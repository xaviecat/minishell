/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:43:43 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/21 14:01:05 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	b_unset(t_msh *sh)
{
	char	**old_envp;
	char	*name_var;
	int		ret_error;

	if (!sh->lst_n->lst_cmd->next)
		return (0);
	sh->lst_n->lst_cmd = sh->lst_n->lst_cmd->next;
	ret_error = string_is_valid(sh->lst_n->lst_cmd);
	if (ret_error > 0)
		return (ret_error);
	while (sh->lst_n->lst_cmd)
	{
		name_var = ft_gbstrdup(sh->lst_n->lst_cmd->cmd, &(sh->garbage));
		check_var_exist(name_var, sh->envp);
		old_envp = ft_gbtabdup(sh->envp, &(sh->garbage));
		if (!old_envp && errno == ENOMEM)
			return (ENOMEM);
		ft_gbtabfree(sh->envp, &(sh->garbage));
		sh->envp = ft_malloc(&(sh->garbage), sizeof(char *),
				length_char_tab(old_envp) + 1);
		unset_tab(sh->envp, old_envp, &(sh->garbage), name_var);
		ft_free(&(sh->garbage), name_var);
		sh->lst_n->lst_cmd = sh->lst_n->lst_cmd->next;
	}
	return (0);
}
