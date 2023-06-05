/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:46:20 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/05 11:35:03 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

size_t	get_arg_count(t_w_cmd_list *curr)
{
	size_t	size;

	size = 0;
	curr = curr->next;
	while (curr)
	{
		curr = curr->next;
		size += 1;
	}
	return (size);
}

int	ft_alloc_envp(t_minish *msh, t_w_cmd_list *curr)
{
	size_t	size_count;
	size_t	i;
	size_t	j;

	msh->envp = ft_malloc(&(msh->garbage), sizeof(char *), get_arg_count(curr) + 1);
	printf("%li\n", get_arg_count(curr));
	if (!(msh->envp))
		return (0);
	curr = curr->next;
	j = 0;
	while (curr)
	{
		size_count = 0;
		i = 0;
		while ((curr->cmd)[i])
		{
			if (size_count || (i && (curr->cmd)[i - 1] == '='))
				size_count++;
			i++;
		}
		if (size_count)
			(msh->envp)[j++] = ft_malloc(&(msh->garbage),
					sizeof(char), size_count);
		curr = curr->next;
	}
	return (1);
}

int	b_export(t_minish *msh, t_w_cmd_list *cmd)
{
	size_t	i;
	char	**save_envp;
	char 	**modified_envp;

	save_envp = msh->envp;
	if (!ft_alloc_envp(msh, cmd))
		return (0);
	cmd = cmd->next;
	i = 0;
	while (cmd)
	{
		if (ft_strchr(cmd->cmd, '='))
			(msh->envp)[i++] = ft_gb_strdup(cmd->cmd, &(msh->garbage));
		cmd = cmd->next;
	}
	msh->envp[i] = NULL;
	modified_envp = ft_gb_dbtab_join(save_envp, msh->envp, &(msh->garbage));
	if (!modified_envp && errno == ENOMEM)
		return (ft_free(&(msh->garbage), msh->envp), 0);
	ft_free(&(msh->garbage), msh->envp);
	msh->envp = modified_envp;
	i = 0;
	while(modified_envp[i])
		printf("%s\n", modified_envp[i++]);
	return (ft_free(&(msh->garbage), save_envp), 1);
}
