/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:46:20 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/07 15:57:00 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

size_t	get_arg_count(t_w_cmd_list *curr, char **envp)
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

int	ft_alloc_envp(t_minish *msh, t_w_cmd_list *curr)
{
	msh->envp = ft_malloc(&(msh->garbage), sizeof(char *),
			get_arg_count(curr, msh->envp) + 1);
	if (!(msh->envp))
		return (0);
	return (1);
}

int	export_print(t_minish *msh)
{
	char	**envp_cpy;
	size_t	i;
	size_t	j;

	if (!msh->envp)
		printf("NULL\n");
	envp_cpy = ft_dbtab_dup_gb(msh->envp, &(msh->garbage));
	ft_sort_str_arr(envp_cpy);
	i = 0;
	while (envp_cpy[i])
	{
		ft_printf("declare -x ");
		j = 0;
		while (envp_cpy[i][j] && envp_cpy[i][j] != '=')
			printf("%c", envp_cpy[i][j++]);
		if (envp_cpy[i][j++])
			printf("=\"%s\"\n", envp_cpy[i] + j);
		else
			printf("\n");
		i++;
	}
	return (1);
}

int	b_export(t_minish *msh, t_w_cmd_list *cmd)
{
	size_t	i;
	char	**save_envp;
	char	**modified_envp;

	if (!cmd->next)
		return (export_print(msh));
	save_envp = msh->envp;
	if (!ft_alloc_envp(msh, cmd))
		return (0);
	cmd = cmd->next;
	i = 0;
	while (cmd)
	{
		if (not_in_env(cmd->cmd, save_envp))
		{
			(msh->envp)[i] = ft_gb_strdup(cmd->cmd, &(msh->garbage));
			if (!(msh->envp[i++]))
				return (0);
		}
		else
			if (!modify_envp(cmd->cmd, save_envp, &(msh->garbage)))
				return (0);
		cmd = cmd->next;
	}
	msh->envp[i] = NULL;
	modified_envp = ft_gb_dbtab_join(save_envp, msh->envp, &(msh->garbage));
	if (!modified_envp && errno == ENOMEM)
		return (ft_free(&(msh->garbage), msh->envp), 0);
	ft_free(&(msh->garbage), msh->envp);
	msh->envp = modified_envp;
	i = 0;
	while (modified_envp[i])
		printf("%s\n", modified_envp[i++]);
	return (ft_free(&(msh->garbage), save_envp), 1);
}
