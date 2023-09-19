/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:36:08 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/30 17:03:34 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**get_path(char **envp, t_garbage **gb)
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

char	**get_cmdpath(char **path, char *cmd, t_garbage **gb)
{
	char	**cmdpath;
	char	*scmd;
	size_t	i;

	i = 0;
	while (path[i])
		i++;
	scmd = ft_gbstrjoin("/", cmd, gb);
	if (!scmd)
		return (NULL);
	cmdpath = ft_malloc(gb, sizeof(char *), i + 1);
	if (!cmdpath)
		return (NULL);
	i = 0;
	while (path[i])
	{
		cmdpath[i] = ft_gbstrjoin(path[i], scmd, gb);
		if (!cmdpath[i])
			return (NULL);
		i++;
	}
	ft_free(gb, scmd);
	cmdpath[i] = NULL;
	return (cmdpath);
}

char	*explore_cmdpaths(char **cmdpaths, t_garbage **gb, bool *f_ok)
{
	size_t		i;
	char		*good_path;

	i = 0;
	while (cmdpaths[i])
	{
		if (!access(cmdpaths[i], F_OK))
			*f_ok = true;
		if (!access(cmdpaths[i], X_OK))
		{
			good_path = ft_gbstrdup(cmdpaths[i], gb);
			if (!good_path)
				return (NULL);
			return (good_path);
		}
		i++;
	}
	return (NULL);
}

char	*check_access(char **cmdpaths, char *cmd, t_garbage **gb)
{
	bool	f_ok;
	char	*good_path;

	f_ok = false;
	good_path = explore_cmdpaths(cmdpaths, gb, &f_ok);
	if (cmd && !cmd[0])
	{
		g_exit_status = 127;
		ft_fdprintf(2, MSH"''"CMD_NOT_FOUND, cmd);
	}
	else if ((!good_path && !f_ok) || ft_strncmp(cmd, "..", 2) == 0)
	{
		g_exit_status = 127;
		ft_fdprintf(2, MSH"%s"CMD_NOT_FOUND, cmd);
	}
	else if (!good_path)
	{
		g_exit_status = 126;
		ft_fdprintf(2, MSH"%s"NO_PERM, cmd);
	}
	ft_gbtabfree(cmdpaths, gb);
	return (good_path);
}

void	cmd_in_current_dir(t_msh *msh, t_node_lst *lst, t_garbage **gb)
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

bool	is_absolute_path(t_node_lst *lst, char **path)
{
	if (!ft_strncmp(lst->lst_cmd->cmd, "./", 2)
		|| !ft_strncmp(lst->lst_cmd->cmd, "/", 1)
		|| ft_strchr(lst->lst_cmd->cmd, '/')
		|| !path)
		return (true);
	return (false);
}

void	give_access(t_msh *msh, char **path, t_node_lst *lst, t_garbage **gb)
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

void	get_access(t_msh *msh)
{
	char	**path;

	path = get_path(msh->envp, &(msh->garbage));
	if (!path && errno == ENOMEM)
		return (free_and_exit_minish(msh));
	give_access(msh, path, msh->lst_n, &(msh->garbage));
}


/*
 * error when permission denied but no when is dir
 * cat | grep | ls | awk | sleep | bash
 * grep | ./cat | ls | awk | sleep | bash
 * cat | grep | ls | awk | ./sleep | bash
 * cat | grep | ls | awk | ./sleep | ./grep
 * ./cat | grep | ls | awk | ./sleep | ./grep
 * ./cat | grep | ls | awk | ./sleep | ./grep -F
 * cat -en << EOF | cat -en | ./grep 'salut' >> "$USER"
 *
 * env | grep 'PATH=' | awk -F: '{gsub(/:/,"\n"); print}'
 */