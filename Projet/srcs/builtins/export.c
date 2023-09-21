/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:46:20 by nfaust            #+#    #+#             */
/*   Updated: 2023/09/21 18:58:27 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

char	*dup_without_plus(char *cmd, t_garbage **gb)
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

int	add_new_var_to_envp(t_cmd_lst *cmd, char **save_envp,
				t_msh *msh, int *error_code)
{
	size_t	i;

	cmd = cmd->next;
	i = 0;
	while (cmd)
	{
		if (!export_error_management(msh, cmd, error_code))
		{
			cmd = cmd->next;
			continue ;
		}
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
	return (msh->envp[i] = NULL, 1);
}

int	b_export(t_msh *msh)
{
	char		**save_envp;
	t_cmd_lst	*cmd;
	char		**modified_envp;
	int			error_code;

	error_code = 0;
	cmd = msh->lst_n->lst_cmd;
	if (!cmd->next)
		return (export_print(msh));
	save_envp = msh->envp;
	if (!ft_alloc_envp(msh, cmd))
		free_and_exit_minish(msh);
	if (!add_new_var_to_envp(cmd, save_envp, msh, &error_code))
		free_and_exit_minish(msh);
	modified_envp = ft_gbtabjoin(save_envp, msh->envp, &(msh->garbage));
	if (!modified_envp && errno == ENOMEM)
		free_and_exit_minish(msh);
	ft_free(&(msh->garbage), msh->envp);
	msh->envp = ft_gbtabdup(modified_envp, &(msh->garbage));
	if (!msh->envp)
		free_and_exit_minish(msh);
	ft_gbtabfree(modified_envp, &(msh->garbage));
	return (ft_free(&(msh->garbage), save_envp), error_code);
}
