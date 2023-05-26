/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:00:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/10 13:18:22 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd_from_envp(char **envp)
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

/* proteger getcwd */
//PWD DISPONIBLE DANS ENVP
void	pwd(char **envp)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		path = get_pwd_from_envp(envp);
	else
		printf("%s\n", path);
	//free(path);
}
