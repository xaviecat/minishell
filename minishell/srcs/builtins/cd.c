/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:36:42 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/03 14:37:58 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_from_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
			return (ft_strdup(envp[i] + 5));
		i++;
	}
	return (NULL);
}

void	cd(char *path, char **envp)
{
	//use HOME from env
	if (path == NULL)
		path = get_home_from_env(envp);
		//SECURISER
	chdir(path);
	 //free(path);
}
