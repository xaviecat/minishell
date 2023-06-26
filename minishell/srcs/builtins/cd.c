/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:36:42 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/21 18:21:45 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_from_env(char **envp, t_garbage **gb)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
			return (ft_gbstrdup(envp[i] + 5, gb));
		i++;
	}
	return (NULL);
}

int	b_cd(t_msh *msh)
{
	char	*path;

	if (msh->lst_n->lst_cmd->next == NULL)
		path = get_home_from_env(msh->envp, &(msh->garbage));
	else
		path = msh->lst_n->lst_cmd->next->cmd;
	if (chdir(path) == -1)
	{
		printf(CD_FILE);
		perror(path);
	}
	return (0);
}
