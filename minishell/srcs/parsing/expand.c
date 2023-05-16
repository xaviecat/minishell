/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:08:17 by nfaust            #+#    #+#             */
/*   Updated: 2023/05/11 18:12:16 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
# define UNKNOWN 0
# define DOUBLE_QUOTE 1

static char	*expand_env_var(char **envp, char *var)
{
	size_t	i;
	size_t	var_len;
	char	*var_expansion;

	if (!envp || !var)
		return (NULL);
	var_len = ft_strlen(var);
	if (var_len == 0)
		return (NULL);
	var_expansion = ft_strjoin(var + 1, "=");
	if (!var_expansion)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_expansion, var_len) == 0)
		{
			free(var_expansion);
			var_expansion = ft_strdup(envp[i] + var_len);
			if (!var_expansion)
				return (NULL);
			return (var_expansion);
		}
		i++;
	}
	return (NULL);
}

static char	*modify_command(char *command, size_t start, char **envp)
{
	char	*env_var;
	char	*expanded_env_var;
	char	*modified_cmd;
	size_t	i;

	env_var = ft_strdup_to_x(command + start, ' '); // remplacer par un isspace !
	if (!env_var)
		return (NULL);
	expanded_env_var = expand_env_var(envp, env_var);
	if (!expanded_env_var)
		return (free(env_var), NULL);
	modified_cmd = malloc(sizeof(char) * (ft_strlen(command)
				+ (ft_strlen(expanded_env_var) - ft_strlen(env_var))));
	free(env_var);
	if (!modified_cmd)
		return (free(expanded_env_var), NULL);
	i = 0;
	while (i++ < start)
		modified_cmd[i - 1] = command[i - 1];
	i = 0;
	while (expanded_env_var[i])
		modified_cmd[start++] = expanded_env_var[i++];
	while (command[start++])
		modified_cmd[start - 1] = command[start - 1];
	return (modified_cmd[start - 1] = 0, free(command), modified_cmd);
}

static char	*expand_vars(char *command, char **envp)
{
	size_t	i;
	int		quote_type;

	i = 0;
	while (command[i])
	{
		quote_type = UNKNOWN;
		if (command[i] == '"')
		{
			quote_type = DOUBLE_QUOTE;
			while (command[i] && command[i] != '$' && command[i] != '"')
				i++;
		}
		if (quote_type == DOUBLE_QUOTE && command[i] && command[i] == '$')
		{
			command = modify_command(command, i, envp);
			if (!command)
				return (NULL);
		}
		if (command[i])
			i++;
	}
	return (command);
}

void	expand_commands(t_word_lst)
{
	t_cmd_list	*cmd_list;

	cmd_list = (*minish)->cmds;
	while (cmd_list)
	{
		cmd_list->cmd[0] = expand_vars(cmd_list->cmd[0], (*minish)->envp);
		if (!cmd_list->cmd[0])
			return ; //code d'erreur a ajouter
		printf("%s\n", cmd_list->cmd[0]);
		cmd_list = cmd_list->next;
	}
}