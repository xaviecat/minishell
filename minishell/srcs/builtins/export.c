/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:46:20 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/01 17:35:58 by nfaust           ###   ########.fr       */
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

void	ft_alloc_envp(t_minish *msh, t_w_cmd_list *curr)
{
	size_t	size_count;
	size_t	i;
	size_t	j;

	msh->envp = ft_malloc(&(msh->garbage), sizeof(char *), get_arg_count(curr));
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
		printf(RED"%li : %li\n"RESET, j, size_count);
		if (size_count)
		{
			(msh->envp)[j] = ft_malloc(&(msh->garbage), sizeof(char), size_count);
			j++;
		}
		curr = curr->next;
	}
}

void	b_export(t_minish *msh, t_w_cmd_list *cmd)
{
	size_t	i;

	ft_alloc_envp(msh, cmd);
	cmd = cmd->next;
	i = 0;
	while (cmd)
	{
		if (ft_strchr(cmd->cmd, '='))
		{
			(msh->envp)[i] = ft_gb_strdup(cmd->cmd, &(msh->garbage));
			i++;
		}
		cmd = cmd->next;
	}
	i = 0;
	while ((msh->envp)[i])
	{
		printf("%s\n", (msh->envp)[i++]);
	}
}