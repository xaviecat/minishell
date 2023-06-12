/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:36:08 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/12 18:06:37 by xcharra          ###   ########.fr       */
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
				return (NULL); //! echec de malloc
			return (path);
		}
		i++;
	}
	return (NULL); //! pas de path dans l'env
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
	cmdpath = ft_malloc(gb, sizeof(char *), i + 1);
	if (!cmdpath)
		return (NULL); //ERROR
	i = 0;
	while (path[i])
	{
		cmdpath[i] = ft_gbstrjoin(path[i], scmd, gb);
		if (!cmdpath[i])
			return (NULL); //ERROR
		i++;
	}
	ft_free(gb, scmd);
	cmdpath[i] = NULL;
	return (cmdpath);
}

char	*dig_for_access(char **cmdpath, char *cmd, t_garbage **gb)
{
	size_t	i;
	bool	f_ok;
//	bool	x_ok;
	char	*good_path;

	i = 0;
	f_ok = false;
//	x_ok = false;
	while (cmdpath[i])
	{
		ft_printf(YELLOW"cmdpath[%d] = %s => ", i, cmdpath[i]);
		if (!access(cmdpath[i], F_OK))
			f_ok = true;
		if (!access(cmdpath[i], X_OK))
		{
			good_path = ft_gbstrdup(cmdpath[i], gb);
			if (!good_path)
				return (NULL);//! ERROR A GERER
			ft_gbtabfree(cmdpath, gb);
			return (good_path);
		}
		i++;
	}
	if (!f_ok) //! check presence puis droit
		return (ft_fdprintf(2, RED"%s"CMD_NOT_FOUND RESET, cmd), NULL); //! retour a gerer
	return (NULL);//! a voir
}

void	get_access(char **path, t_cmd_list **lst_cmds, t_garbage **gb)
{
	t_cmd_list	*first;
	char		**cmdpath;

	first = *lst_cmds;
	while (*lst_cmds)
	{
		cmdpath = get_cmdpath(path, (*lst_cmds)->cmd->cmd, gb);
		(*lst_cmds)->cmdpath = dig_for_access(cmdpath, (*lst_cmds)->cmd->cmd, gb);
		ft_printf(PURPLE"right path = %s\n"RESET, (*lst_cmds)->cmdpath);
		if (!((*lst_cmds)->cmdpath))
			return ((void) ft_printf(RED"ERROR ???"RESET)); //! ERROR A GERER
		(*lst_cmds) = (*lst_cmds)->next;
	}
	ft_gbtabfree(path, gb);
	ft_gbtabfree(cmdpath, gb);
	(*lst_cmds) = first;
	return ;
}

void	placeholder(t_minish **sh)
{
	char	**path;

	path = get_path((*sh)->envp, &((*sh)->garbage));
	get_access(path, &((*sh)->cmds), &((*sh)->garbage));
}

/*
 * **splited_path = gbsplit()
 */
