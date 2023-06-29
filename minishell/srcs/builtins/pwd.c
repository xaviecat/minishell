/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:00:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/16 16:37:22 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pwd_from_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			return (ft_strdup(envp[i] + 4));
		i++;
	}
	return (NULL);
}

int	b_pwd(t_msh *msh)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		path = get_pwd_from_envp(msh->envp);
	printf("%s\n", path);
	free(path);
	return (0);
}
