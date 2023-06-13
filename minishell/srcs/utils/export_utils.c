/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:17:59 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/13 12:06:01 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static size_t	get_var_name_len(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
		i++;
	return (i);
}

int	concat_var(char *cmd, size_t var_name_len, t_garbage **gb, char **envp)
{
	size_t	i;

	printf("concatening var...\n");
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], cmd, var_name_len - 1)
			&& (!envp[i][var_name_len] || envp[i][var_name_len] == '='))
			break ;
		i++;
	}
	if (envp[i][var_name_len] && envp[i][var_name_len + 1])
		var_name_len++;
	envp[i] = ft_gbstrjoin(envp[i], cmd + var_name_len + 1, gb);
	if (!envp[i])
		return (0);
	return (1);
}

int	modify_envp(char *cmd, char **envp, t_garbage **gb)
{
	size_t	i;
	size_t	var_name_len;

	var_name_len = get_var_name_len(cmd);
	if (cmd[var_name_len] == '+')
		return (concat_var(cmd, var_name_len, gb, envp));
	i = 0;
	while (ft_strncmp(cmd, envp[i++], var_name_len))
		i++;
	i--;
	ft_free(gb, envp[i]);
	envp[i] = ft_gb_strdup(cmd, gb);
	if (!envp[i])
		return (0);
	return (1);
}

int is_concat(char *cmd)
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

int cmp_concat(char **envp, char *cmd)
{
	size_t	i;
	size_t	var_len;

	var_len = 0;
	while (cmd[var_len] != '+')
		var_len++;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(cmd, envp[i], var_len - 1))
			if (!envp[i][var_len] || envp[i][var_len] == '=')
				return (0);
		i++;
	}
	return (1);
}

int	not_in_env(char *cmd, char **envp)
{
	size_t	i;
	size_t	var_name_len;

	if (is_concat(cmd))
		return (cmp_concat(envp, cmd));
	var_name_len = get_var_name_len(cmd);
	i = 0;
	while (envp[i])
	{
		if (ft_strlen(envp[i]) == var_name_len)
		{
			if (!ft_strncmp(cmd, envp[i++], var_name_len))
				return (0);
		}
		else if (!ft_strncmp(cmd, envp[i++], var_name_len + 1))
			return (0);
	}
	return (1);
}
