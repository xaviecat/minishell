/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_routine_and_end.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:46:50 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/27 13:38:56 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	free_and_exit_minish(t_msh *minish, char **envp_sh)
{
	if (envp_sh)
		ft_tabfree(envp_sh);
	ft_free_all(&(minish->garbage));
	free(minish->garbage);
	free(minish);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	free_end_loop(t_msh *msh, char ***envp_sh)
{
	*envp_sh = cp_envp_to_envp_sh(*envp_sh, msh);
	ft_free_all(&msh->garbage);
	msh->lst_n = NULL;
	free(msh->garbage);
	msh->garbage = NULL;
	free(msh);
	msh = NULL;
}

char	**cp_envp_to_envp_sh(char **envp_sh, t_msh *msh)
{
	if (envp_sh)
		ft_tabfree(envp_sh);
	envp_sh = ft_tabdup(msh->envp);
	if (!envp_sh)
		free_and_exit_minish(msh, envp_sh);
	return (envp_sh);
}

int	routine_minishell(t_msh *msh, char *line, char ***envp_sh)
{
	if (!parsing_char(&msh, line, envp_sh))
		return (1);
	if (!parsing_word(&msh, envp_sh))
		return (1);
	if (!parsing_cmd(&msh, envp_sh))
		return (1);
	if (!get_cmdtab(msh))
		free_and_exit_minish(msh, *envp_sh);
	ft_tabfree(*envp_sh);
	*envp_sh = NULL;
	execution(msh);
	return (0);
}
