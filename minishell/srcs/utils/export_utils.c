/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:17:59 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/05 14:23:37 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static size_t	get_var_name_len(char *arg)
{
	size_t	i;
//	char	*var_name;
//
//	i = 0;
//	while (arg[i] != '=')
//		i++;
//	var_name = ft_malloc(gb, sizeof(char), i + 2);
//	if (!var_name)
//		return (NULL);
//	i = 0;
//	while (arg[i++] != '=')
//		var_name[i - 1] = arg[i - 1];
//	var_name[i] = 0;
//	return (var_name);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i + 1);
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
	envp[i] = ft_gbstrdup(cmd, gb);
	if (!envp[i])
		return (0);
	return (1);
}

int	not_in_env(char *cmd, char **envp)
{
	size_t	i;
	size_t	var_name_len;

	var_name_len = get_var_name_len(cmd);
	i = 0;
	while (envp[i])
		if (!ft_strncmp(cmd, envp[i++], var_name_len))
			return (0);
	return (1);
}
