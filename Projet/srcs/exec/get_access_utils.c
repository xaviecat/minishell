/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_access_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:44:20 by xcharra           #+#    #+#             */
/*   Updated: 2023/10/03 13:32:52 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Iterate through the cmdpaths and check if any path lead to the command
 * and if it's executable
 * @param cmdpaths
 * @param f_ok pointer to a bool which is true if the command is in the path and
 * false if the opposite
 * @return the right command path or NULL in case of error or command not found
 * in the paths
 */
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

/**
 * @brief Check when the good path is null why and display the appropriate error
 * @param cmdpaths all path concatenate with the command name
 * @param cmd command name
 * @return the path which execve can execute the command
 */
char	*check_access(char **cmdpaths, char *cmd, t_garbage **gb)
{
	bool	f_ok;
	char	*good_path;

	f_ok = false;
	good_path = explore_cmdpaths(cmdpaths, gb, &f_ok);
	if (cmd && !cmd[0])
	{
		g_exit_status = 127;
		ft_fdprintf(2, MSH"''"CMD_NOT_FOUND);
	}
	else if ((!good_path && !f_ok && errno != ENOMEM)
		|| ft_strncmp(cmd, "..", 2) == 0)
	{
		g_exit_status = 127;
		ft_fdprintf(2, MSH"%s"CMD_NOT_FOUND, cmd);
	}
	else if (!good_path && errno != ENOMEM)
	{
		g_exit_status = 126;
		ft_fdprintf(2, MSH"%s"NO_PERM, cmd);
	}
	ft_gbtabfree(cmdpaths, gb);
	return (good_path);
}

/**
 * @brief Concatenate command name and each command path
 * @param path all command path extracted from env
 * @param cmd command name
 * @return all path concatenate with the command name
 */
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
