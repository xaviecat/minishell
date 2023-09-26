/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_expand_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:37:58 by nfaust            #+#    #+#             */
/*   Updated: 2023/09/26 10:18:19 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static char	*get_var_value(char **envp, char *var_expansion,
					size_t var_len, t_garbage **gb)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i++], var_expansion, var_len) == 0)
		{
			ft_free(gb, var_expansion);
			var_expansion = ft_gbstrdup(envp[i - 1] + var_len, gb);
			if (!var_expansion)
				return (NULL); //! mettre un free and exit
			return (var_expansion);
		}
	}
	return (NULL);
}

/**
 * @brief collect the content of the environnement variable
 * @param envp
 * @param var the environnement variable
 * @return the content of the environnement variable, \n\n
 * an allocated string containing "" if the variable is not set
 */
static char	*expand_env_var(t_garbage **gb, char **envp, char *var)
{
	size_t	var_len;
	char	*var_expansion;

	if (!envp || !var)
		return (NULL);
	var_len = ft_strlen(var);
	if (var_len == 0)
		return (NULL);
	if (!ft_strncmp("$?", var, 3))
		return (ft_gbitoa(g_exit_status, gb));
	var_expansion = ft_gbstrjoin(var + 1, "=", gb);
	if (!var_expansion)
		return (NULL);
	var_expansion = get_var_value(envp, var_expansion, var_len, gb);
	if (var_expansion)
		return (var_expansion);
	return (ft_free(gb, var_expansion), ft_gbstrdup("", gb));
}

/**
 * @brief collect the content of the environnement
 * variable and cut spaces in it if needed
 * @param env_var the environnement variable
 * @param double_not_closed 1 if a double quote is opened, \n 0 if not
 * @param envp
 * @return the content of the environnement variable
 */
char	*set_expanded_env_var(char *env_var, t_msh *msh,
						int double_not_closed)
{
	char	*expanded_env_var;

	expanded_env_var = expand_env_var(&(msh->garbage), msh->envp, env_var);
	if (double_not_closed < 0)
		expanded_env_var = cut_whitespaces(expanded_env_var, &((*msh).garbage));
	if (!expanded_env_var)
		return (NULL);
	return (expanded_env_var);
}
