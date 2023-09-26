/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:36:08 by xcharra           #+#    #+#             */
/*   Updated: 2023/09/21 21:49:37 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Iterate trough the environnement variables to find the path
 * @param envp environnement variables
 * @return all paths extracted from env or NULL if error or no path in
 * env
 */
static char	**get_path(char **envp, t_garbage **gb)
{
	size_t	i;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_gbsplit(ft_strchr(envp[i], '=') + 1, ':', gb);
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

/**
 * @brief Check access of the command written with a path and if none returns
 * an error then returns the native command
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 * @param lst actual command node of the list
 */
static void	cmd_in_current_dir(t_msh *msh, t_node_lst *lst, t_garbage **gb)
{
	struct stat	st;

	if (access(lst->lst_cmd->cmd, F_OK))
	{
		g_exit_status = 127;
		ft_fdprintf(2, MSH"%s"NO_SFD, lst->lst_cmd->cmd);
		return ;
	}
	stat(lst->lst_cmd->cmd, &st);
	if (S_ISDIR(st.st_mode))
	{
		g_exit_status = 126;
		ft_fdprintf(2, MSH"%s"IS_DIR, lst->lst_cmd->cmd);
		return ;
	}
	if (access(lst->lst_cmd->cmd, X_OK))
	{
		g_exit_status = 126;
		ft_fdprintf(2, MSH"%s"NO_PERM, lst->lst_cmd->cmd);
		return ;
	}
	lst->cmdpath = ft_gbstrdup(lst->lst_cmd->cmd, gb);
	if (!(lst->cmdpath) && errno == ENOMEM)
		return (free_and_exit_minish(msh));
}

/**
 * @brief Check if the command is written with a path
 * @param lst actual command node of the list
 * @param path all command path extracted from env
 */
static bool	is_absolute_path(t_node_lst *lst, char **path)
{
	if (!ft_strncmp(lst->lst_cmd->cmd, "./", 2)
		|| !ft_strncmp(lst->lst_cmd->cmd, "/", 1)
		|| ft_strchr(lst->lst_cmd->cmd, '/')
		|| !path)
		return (true);
	return (false);
}

/**
 * @brief Iterate through the node list to get command paths and send them to
 * check access function
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 * @param path all command path extracted from env
 * @param lst list of nodes which contain command
 */
static void	give_access(t_msh *msh, char **path, t_node_lst *lst,
	t_garbage **gb)
{
	t_node_lst	*first;
	char		**cmdpaths;

	first = lst;
	while (lst)
	{
		if (lst->builtin < e_none || !(lst->lst_cmd))
			lst->cmdpath = NULL;
		else if (is_absolute_path(lst, path))
			cmd_in_current_dir(msh, lst, gb);
		else
		{
			cmdpaths = get_cmdpath(path, lst->lst_cmd->cmd, gb);
			lst->cmdpath = check_access(cmdpaths, lst->lst_cmd->cmd, gb);
			if ((!cmdpaths || !(lst->cmdpath)) && errno == ENOMEM)
				return (free_and_exit_minish(msh));
		}
		lst = lst->next;
	}
	ft_gbtabfree(path, gb);
	lst = first;
}

/**
 * @brief Get the path in the env and give it to give access function
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 */
void	get_access(t_msh *msh)
{
	char	**path;

	path = get_path(msh->envp, &(msh->garbage));
	if (!path && errno == ENOMEM)
		return (free_and_exit_minish(msh));
	give_access(msh, path, msh->lst_n, &(msh->garbage));
}
