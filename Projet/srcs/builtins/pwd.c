/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:00:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/09/19 11:34:06 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

//static char	*get_pwd_from_envp(char **envp)
//{
//	int	i;
//
//	i = 0;
//	while (envp[i])
//	{
//		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
//			return (ft_strdup(envp[i] + 4));
//		i++;
//	}
//	return (NULL);
//}

int	b_pwd(t_msh *msh)
{
	char	*path;

	if (ft_strchr(msh->lst_n->lst_cmd->next->cmd, '-') != NULL)
	{
		return (ft_fdprintf(2, RED MSH E_PWD INV_OPT RESET), 2);
	}
	path = getcwd(NULL, 0);
	//if (!path)
		//path = get_pwd_from_envp(msh->envp);
	printf("%s\n", path);
	free(path);
	return (0);
}
