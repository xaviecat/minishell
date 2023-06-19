/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:36:08 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/15 17:16:07 by xcharra          ###   ########.fr       */
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
		return (NULL); //!ERROR
	i = 0;
	while (path[i])
	{
		cmdpath[i] = ft_gbstrjoin(path[i], scmd, gb);
		if (!cmdpath[i])
			return (NULL); //!ERROR
		i++;
	}
	ft_free(gb, scmd);
	cmdpath[i] = NULL;
	return (cmdpath);
}

char	*check_access(char **cmdpaths, char *cmd, t_garbage **gb)
{
	size_t		i;
	bool		f_ok;
	char		*good_path;


	i = 0;
	f_ok = false;
	while (cmdpaths[i])
	{
		if (!access(cmdpaths[i], F_OK))
			f_ok = true;
		if (!access(cmdpaths[i], X_OK))
		{
			good_path = ft_gbstrdup(cmdpaths[i], gb);
			if (!good_path)
				return (NULL); //! MALLOC ERROR
			ft_gbtabfree(cmdpaths, gb);
			return (good_path);
		}
		i++;
	}
	if (!f_ok)
		return (ft_fdprintf(2, RED"%s"CMD_NOT_FOUND RESET, cmd), NULL); //! retour a gerer
	perror(cmd);
	return (NULL);//! a voir
}

void	cmd_in_current_dir(t_node_lst **lst, t_garbage **gb)
{
	struct stat	st;

	if (access((*lst)->lst_cmd->cmd, F_OK))
		return ((void)ft_fdprintf(2, RED MSH "%s" NO_SFD RESET, (*lst)->lst_cmd->cmd));
	stat((*lst)->lst_cmd->cmd, &st);
	if (S_ISDIR(st.st_mode))
		return ((void)ft_fdprintf(2, RED MSH"%s" IS_DI RESET, (*lst)->lst_cmd->cmd));
	if (access((*lst)->lst_cmd->cmd, X_OK))
		return ((void)ft_fdprintf(2, RED MSH"%s" NO_PERM RESET, (*lst)->lst_cmd->cmd));
	(*lst)->cmdpath = ft_gbstrdup((*lst)->lst_cmd->cmd, gb);
	if (!((*lst)->cmdpath))
		return ; //!ERROR
	return ;

}

void	give_access(char **path, t_node_lst **lst, t_garbage **gb)
{
	t_node_lst	*first;
	char		**cmdpaths;

	first = *lst;
	while (*lst)
	{
		if (!((*lst)->lst_cmd))
		{
			(*lst)->cmdpath = NULL;
			(*lst) = (*lst)->next;
			continue ;
		}
		if (!ft_strncmp((*lst)->lst_cmd->cmd, "./", 2)
			|| !ft_strncmp((*lst)->lst_cmd->cmd, "/", 1)
			|| ft_strchr((*lst)->lst_cmd->cmd, '/'))
		{
			cmd_in_current_dir(lst, gb);
			(*lst) = (*lst)->next;
			continue ;
		}
		cmdpaths = get_cmdpath(path, (*lst)->lst_cmd->cmd, gb);
		(*lst)->cmdpath = check_access(cmdpaths, (*lst)->lst_cmd->cmd, gb);
		if (!((*lst)->cmdpath))
			return ;//ft_fdprintf(2, RED"no path%s\n"RESET, (*lst)->lst_cmd->lst_cmd) //! ERROR A GERER
		(*lst) = (*lst)->next;
	}
	ft_gbtabfree(path, gb);
	(*lst) = first;
	return ;
}

void	get_access(t_msh **sh)
{
	char	**path;

	path = get_path((*sh)->envp, &((*sh)->garbage));
	if (!path)
	{
		if (errno == ENOMEM)
			return ((void)ft_fdprintf(2, RED"malloc error in get_path\n"RESET));
		else
			return ((void)ft_fdprintf(2, RED"no path in env\n"RESET));
	}
	give_access(path, &((*sh)->lst_n), &((*sh)->garbage));
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