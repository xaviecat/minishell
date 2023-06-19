/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:46:20 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/15 17:07:24 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

size_t	get_arg_count(t_cmd_lst *curr, char **envp)
{
	size_t	size;

	size = 0;
	curr = curr->next;
	while (curr)
	{
		if (not_in_env(curr->cmd, envp))
			size += 1;
		curr = curr->next;
	}
	return (size);
}

int	ft_alloc_envp(t_msh *msh, t_cmd_lst *curr)
{
	msh->envp = ft_malloc(&(msh->garbage), sizeof(char *),
			get_arg_count(curr, msh->envp) + 1);
	if (!(msh->envp))
		return (0);
	return (1);
}

int	contain_dquote(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		if (str[i++] == '"')
			return (1);
	return (0);
}

void	print_with_backslash(char *str)
{
	size_t	i;

	i = 0;
	printf("=\"");
	while (str[i])
	{
		if (str[i] == '"')
			printf("\\%c", str[i]);
		else
			printf("%c", str[i]);
		i++;
	}
	printf("\"\n");
}

int	export_print(t_msh *msh)
{
	char	**envp_cpy;
	size_t	i;
	size_t	j;

	envp_cpy = ft_gbtabdup(msh->envp, &(msh->garbage));
	ft_sort_str_arr(envp_cpy);
	i = 0;
	while (envp_cpy[i])
	{
		ft_printf("declare -x ");
		j = 0;
		while (envp_cpy[i][j] && envp_cpy[i][j] != '=')
			printf("%c", envp_cpy[i][j++]);
		if (envp_cpy[i][j] && contain_dquote(envp_cpy[i] + j))
			print_with_backslash(envp_cpy[i] + j + 1);
		else if (envp_cpy[i][j++])
			printf("=\"%s\"\n", envp_cpy[i] + j);
		else
			printf("\n");
		i++;
	}
	return (1);
}

char *dup_without_plus(char *cmd, t_garbage **gb)
{
	size_t	i;
	size_t	j;
	char	*new_cmd;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] != '+')
			j++;
		i++;
	}
	new_cmd = ft_malloc(gb, sizeof(char), j + 1);
	if (!new_cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
		if (cmd[i++] != '+')
			new_cmd[j++] = cmd[i - 1];
	new_cmd[j] = 0;
	return (new_cmd);
}

int	add_new_var_to_envp(t_cmd_lst *cmd, char **save_envp, t_msh *msh)
{
	size_t	i;

	cmd = cmd->next;
	i = 0;
	while (cmd)
	{
		if (not_in_env(cmd->cmd, save_envp))
		{
			if (!is_concat(cmd->cmd))
				(msh->envp)[i] = ft_gbstrdup(cmd->cmd, &(msh->garbage));
			else
				msh->envp[i] = dup_without_plus(cmd->cmd, &(msh->garbage));
			if (!(msh->envp[i++]))
				return (0);
		}
		else if (!modify_envp(cmd->cmd, save_envp, &(msh->garbage)))
			return (0);
		cmd = cmd->next;
	}
	msh->envp[i] = NULL;
	return (1);
}

int	b_export(t_msh *msh, t_cmd_lst *cmd)
{
	char	**save_envp;
	char	**modified_envp;

	if (!cmd->next || (cmd->next && *(cmd->next->cmd) == 0))
		return (export_print(msh));
	if (!export_error_management(msh, cmd))
		return (1);
	save_envp = msh->envp;
	if (!ft_alloc_envp(msh, cmd))
		return (0);
	if (!add_new_var_to_envp(cmd, save_envp, msh))
		return (0);
	modified_envp = ft_gbtabjoin(save_envp, msh->envp, &(msh->garbage));
	if (!modified_envp && errno == ENOMEM)
		return (ft_free(&(msh->garbage), msh->envp), 0);
	ft_free(&(msh->garbage), msh->envp);
	msh->envp = modified_envp;
	return (ft_free(&(msh->garbage), save_envp), 1);
}
