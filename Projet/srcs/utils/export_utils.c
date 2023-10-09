/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:17:59 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/05 18:18:27 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/***
 * @brief gets the length of the variable name
 * @param arg
 * @return
 */
size_t	get_var_name_len(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
		i++;
	return (i);
}

/***
 * @brief concatenates the content to be added into the
 * variable with the old content
 * @param cmd the variable (name+content)
 * @param var_name_len the length of the variable name
 * @param gb
 * @param envp
 * @return 0 on failure, 1 on success
 */
int	concat_var(char *cmd, size_t var_name_len, t_garbage **gb, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], cmd, var_name_len)
			&& (!envp[i][var_name_len] || envp[i][var_name_len] == '='))
			break ;
		i++;
	}
	if (envp[i][var_name_len])
		var_name_len++;
	envp[i] = ft_gbstrjoin(envp[i], cmd + var_name_len + 1, gb);
	if (!envp[i])
		return (0);
	return (1);
}

/***
 * @brief modifies the current envp to add or concatenate the new variables
 * @param cmd the entire variable (name+content)
 * @param envp
 * @param gb
 * @return 0 on failure, 1 on success
 */
int	modify_envp(char *cmd, char **envp, t_garbage **gb)
{
	size_t	i;
	size_t	var_name_len;

	var_name_len = get_var_name_len(cmd);
	if (cmd[var_name_len] == '+')
		return (concat_var(cmd, var_name_len, gb, envp));
	i = 0;
	while (ft_strncmp(cmd, envp[i], var_name_len))
		i++;
	if (envp[i][var_name_len] && !cmd[var_name_len])
		return (1);
	ft_free(gb, envp[i]);
	envp[i] = ft_gbstrdup(cmd, gb);
	if (!envp[i])
		return (0);
	return (1);
}

/***
 * @brief checks whether a variable change is a concatenation or not
 * @param cmd
 * @return 0 if it's an assignation, 1 if it's a concatenation
 */
int	is_concat(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (0);
		else if (cmd[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief checks whether a concatenation is in env or not
 * @param envp
 * @param cmd the entire command (name+content)
 * @return 0 if found in envp, else 1
 */
int	cmp_concat(char **envp, char *cmd)
{
	size_t	i;
	size_t	var_len;

	var_len = 0;
	while (cmd[var_len] != '+')
		var_len++;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(cmd, envp[i], var_len))
			if (!envp[i][var_len] || envp[i][var_len] == '=')
				return (0);
		i++;
	}
	return (1);
}
