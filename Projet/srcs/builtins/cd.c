/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:36:42 by xcharra           #+#    #+#             */
/*   Updated: 2023/09/19 11:45:32 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
	int		i;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
		{
			temp = getcwd(NULL, 0);
			ft_free(gb, envp[i]);
			envp[i] = ft_gbstrjoin("OLDPWD=",
					ft_gbstrdup(temp, gb), gb);
			free(temp);
		}
		i++;
	}
}

static void	update_pwd(char **envp, t_garbage **gb)
{
	int		i;
	char	*new_pwd;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			ft_free(gb, envp[i]);
			new_pwd = getcwd(NULL, 0);
			envp[i] = ft_gbstrjoin("PWD=", new_pwd, gb);
			free(new_pwd);
		}
		i++;
	}
}

static char	*get_path_from_env(t_msh *msh)
{
	if (msh->lst_n->lst_cmd->next == NULL
		|| (msh->lst_n->lst_cmd->next != NULL
			&& msh->lst_n->lst_cmd->next->cmd != NULL
			&& (ft_strncmp(msh->lst_n->lst_cmd->next->cmd, "~", 2) == 0
				|| ft_strncmp(msh->lst_n->lst_cmd->next->cmd, "~/", 3) == 0)))
		return (get_home_from_env(msh->envp, &(msh->garbage)));
	return (NULL);
}

int	b_cd(t_msh *msh)
{
	char	*path;

	path = get_path_from_env(msh);
	if (path == NULL)
	{
		path = msh->lst_n->lst_cmd->next->cmd;
		if (msh->lst_n->lst_cmd->next->next)
			return (ft_fdprintf(2, RED MSH E_CD TOO_MN_ARGS RESET), 1);
	}
	if (ft_strncmp(msh->lst_n->lst_cmd->next->cmd, "---", 4) == 0)
		return (ft_fdprintf(2, RED MSH E_CD INV_OPT RESET), 2);
	if (ft_strncmp(path, ".", 2) == 0)
		update_old_pwd(msh->envp, &(msh->garbage));
	if (chdir(path) == -1)
	{
		ft_fdprintf(2, E_CD);
		perror(path);
		return (1);
	}
	else
		update_pwd(msh->envp, &(msh->garbage));
	return (0);
}
