/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_routine_and_end.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:46:50 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/21 21:40:59 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit_minish(t_msh *minish)
{
	ft_free_all(&(minish->garbage));
	free(minish->garbage);
	free(minish);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	free_end_loop(t_msh *msh)
{
	ft_free_all(&msh->garbage);
	free(msh->garbage);
	free(msh);
}

char	**cp_envp_to_envp_sh(char **envp_sh, char **envp_in_minish)
{
	envp_sh = ft_tabdup(envp_in_minish);
	return (envp_sh);
}

int	routine_minishell(t_msh *msh, char *line)
{
	if (!parsing_char(&msh, line))
		return (1);
	if (!parsing_word(&msh))
		return (1);
	if (!parsing_cmd(&msh))
		return (1);
	if (!get_cmdtab(msh))
		free_and_exit_minish(msh);
	execution(msh);
	return (0);
}
