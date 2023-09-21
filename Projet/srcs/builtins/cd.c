/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:36:42 by xcharra           #+#    #+#             */
/*   Updated: 2023/09/21 13:45:38 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief return HOME variable from the envp
 * @param envp
 * @param gb
 * @return the path of HOME
 */
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

/**
 * @brief Update the OLDPWD variable in envp
 * @param envp
 * @param gb
 * @return 1 if there is a malloc error, 0 if not
 */
static int	update_old_pwd(char **envp, t_garbage **gb)
{
	int		i;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
		{
			temp = getcwd(NULL, 0);
			if (!temp)
				return (0);
			ft_free(gb, envp[i]);
			envp[i] = ft_gbstrjoin("OLDPWD=", temp, gb);
			free(temp);
			if (!envp[i])
				return (1);
			break ;
		}
		i++;
	}
	return (0);
}

/**
 * @brief Update the current pwd in envp
 * @param envp
 * @param gb
 * @return 1 if there is a malloc error, 0 if not
 */
static int	update_pwd(char **envp, t_garbage **gb)
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
			if (!new_pwd)
				return (0);
			envp[i] = ft_gbstrjoin("PWD=", new_pwd, gb);
			free(new_pwd);
			if (!envp[i])
				return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief check if you need to get the HOME from envp
 * @param msh
 * @return HOME content if you should get it, NULL instead
 */
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

/**
 * @brief Use to navigate from dir to dir, and change the PWD and OLDPWD in envp
 * @param msh
 * @return 1 or 2 if there is an error, 0 instead
 */
int	b_cd(t_msh *msh)
{
	char	*path;

	path = get_path_from_env(msh);
	if (path == NULL)
	{
		path = msh->lst_n->lst_cmd->next->cmd;
		if (msh->lst_n->lst_cmd->next->next)
			return (ft_fdprintf(2, MSH E_CD TOO_MN_ARGS), 1);
		if (ft_strncmp(msh->lst_n->lst_cmd->next->cmd, "---", 4) == 0)
			return (ft_fdprintf(2, MSH E_CD INV_OPT), 2);
	}
	if (ft_strncmp(path, ".", 2) == 0)
		if (update_old_pwd(msh->envp, &(msh->garbage)))
			free_and_exit_minish(msh);
	if (chdir(path) == -1)
	{
		ft_fdprintf(2, E_CD);
		perror(path);
		return (1);
	}
	else
		if (update_pwd(msh->envp, &(msh->garbage)))
			free_and_exit_minish(msh);
	return (0);
}
