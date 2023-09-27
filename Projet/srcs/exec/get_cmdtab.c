/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:36:12 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/21 17:23:51 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Get the t_cmd_lst size
 * @param lst
 * @return size of the list
 */
static int	lst_size(t_cmd_lst *lst)
{
	size_t		i;
	t_cmd_lst	*first;

	i = 0;
	first = lst;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	lst = first;
	return (i);
}

/**
 * @brief convert the lst_cmd (chained list) in cmdtab (char **) for execve
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 * @return
 */
static char	**create_cmdtab(t_cmd_lst *lst, t_garbage **gb)
{
	size_t		i;
	char		**cmdtab;

	i = lst_size(lst);
	cmdtab = ft_malloc(gb, sizeof(char *), i + 1);
	if (!cmdtab)
		return (NULL);
	i = 0;
	while (lst)
	{
		cmdtab[i] = ft_gbstrdup(lst->cmd, gb);
		if (!cmdtab[i])
			return (NULL);
		i++;
		lst = lst->next;
	}
	cmdtab[i] = NULL;
	return (cmdtab);
}

/**
 * @brief convert the lst_cmd (chained list) in cmdtab (char **) for execve
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 * @return 0 if error, 1 if success
 */
int	get_cmdtab(t_msh *msh)
{
	t_node_lst	*first;

	first = msh->lst_n;
	while (msh->lst_n)
	{
		if (msh->lst_n->lst_cmd)
		{
			msh->lst_n->cmdtab = create_cmdtab(msh->lst_n->lst_cmd,
					&(msh->garbage));
			if (!msh->lst_n->cmdtab)
				return (0);
		}
		msh->lst_n = msh->lst_n->next;
	}
	msh->lst_n = first;
	return (1);
}
