/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:36:42 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/22 17:28:12 by syluiset         ###   ########.fr       */
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

static void	update_old_pwd(char **envp, t_garbage **gb)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
		{
			ft_free(gb, envp[i]);
			envp[i] = ft_gbstrjoin("OLDPWD=",
					ft_gbstrdup(getcwd(NULL, 0), gb), gb);
		}
		i++;
	}
}

static void	update_pwd(char **envp, t_garbage **gb)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			ft_free(gb, envp[i]);
			envp[i] = ft_gbstrjoin("PWD=",
					ft_gbstrdup(getcwd(NULL, 0), gb), gb);
		}
		i++;
	}
}

int	b_cd(t_msh *msh)
{
	char	*path;

	if (msh->lst_n->lst_cmd->next == NULL)
		path = get_home_from_env(msh->envp, &(msh->garbage));
	else
		path = msh->lst_n->lst_cmd->next->cmd;
	if (msh->lst_n->lst_cmd->next->next)
	{
		ft_fdprintf(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	if (ft_strncmp(path, ".", 2) == 0)
		update_old_pwd(msh->envp, &(msh->garbage));
	if (chdir(path) == -1)
	{
		printf("cc");
		ft_fdprintf(2, CD_FILE);
		perror(path);
		return (1);
	}
	else
		update_pwd(msh->envp, &(msh->garbage));
	return (0);
}
