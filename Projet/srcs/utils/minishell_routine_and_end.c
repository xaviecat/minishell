/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_routine_and_end.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:46:50 by syluiset          #+#    #+#             */
/*   Updated: 2023/10/10 00:16:32 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/**
 * @brief free all malloc variables stock in garbage, free structures and envp
 * when we have to exit program
 * @param msh contains all data
 * @param envp_sh
 * @param exit_code
*/
void	free_and_exit_minish(t_msh *msh, char **envp_sh, int exit_code)
{
	if (envp_sh)
		ft_tabfree(envp_sh);
	ft_free_all(&(msh->garbage));
	free(msh->garbage);
	msh->garbage = NULL;
	free(msh);
	msh = NULL;
	rl_clear_history();
	exit(exit_code);
}

/** 
 * @brief free all variable in garbage collector and structures
 * @param msh contains all data
 * @param envp_sh
*/
void	free_end_loop(t_msh *msh, char ***envp_sh)
{
	*envp_sh = cp_envp_to_envp_sh(*envp_sh, msh);
	close_all(NULL, msh);
	ft_free_all(&msh->garbage);
	msh->lst_n = NULL;
	free(msh->garbage);
	msh->garbage = NULL;
	free(msh);
	msh = NULL;
}
/**
 * @brief copy the envp stock in msh in envp_sh
 * @param envp_sh
 * @param msh
 * @return the envp stock in msh in a string tab
*/
char	**cp_envp_to_envp_sh(char **envp_sh, t_msh *msh)
{
	if (envp_sh)
		ft_tabfree(envp_sh);
	envp_sh = ft_tabdup(msh->envp);
	if (!envp_sh)
		free_and_exit_minish(msh, envp_sh, EXIT_FAILURE);
	return (envp_sh);
}

/**
 * @brief parsing all data in msh
 * @param msh
 * @param line
 * @return 1 if an error occurs, 0 is function work fine
*/
int	routine_minishell(t_msh *msh, char *line, char ***envp_sh)
{
	if (!parsing_char(&msh, line, envp_sh))
		return (1);
	if (!parsing_word(&msh, envp_sh))
		return (1);
	if (!parsing_cmd(&msh, envp_sh))
		return (1);
	if (!get_cmdtab(msh))
		free_and_exit_minish(msh, *envp_sh, EXIT_FAILURE);
	ft_tabfree(*envp_sh);
	*envp_sh = NULL;
	execution(msh);
	return (0);
}
