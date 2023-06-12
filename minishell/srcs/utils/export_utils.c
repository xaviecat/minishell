/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:17:59 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/12 18:00:39 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static size_t	get_var_name_len(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

size_t	modify_envp(char *cmd, char **envp, t_garbage **gb)
{
	size_t	i;
	size_t	var_name_len;

	var_name_len = get_var_name_len(cmd);
	i = 0;
	while (envp[i])
		if (!ft_strncmp(cmd, envp[i++], var_name_len))
			break ;
	i--;
//	printf("\n\n%s\n\n", envp[i]);
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
		{
			if (envp)
			return (1);
		}
		i++;
	}
	return (0);
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
