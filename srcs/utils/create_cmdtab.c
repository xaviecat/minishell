/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmdtab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:36:12 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/26 13:59:41 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @param lst the list which contain a command with his arguments
 * @return The size of the list
 */
int	lst_size(t_cmd_lst *lst)
{
	t_cmd_lst	*first;
	size_t		i;

	first = lst;
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	lst = first;
}

/**
 * @brief Create a new tab with the command and his arguments from the cmd_list
 * for execve
 * @param lst the list which contain a command with his arguments
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 * @return the new fresh malloc'd tab or NULL if there are an error
 */
char	**create_cmdtab(t_cmd_lst *lst, t_garbage **gb, t_msh *msh)
{
	size_t		i;
	char		**cmdtab;

	i = lst_size(lst);
	cmdtab = ft_malloc(gb, sizeof(char *), i + 1);
	if (!cmdtab)
		return (free_and_exit_minish(msh, NULL, EXIT_FAILURE), NULL);
	i = 0;
	while (lst)
	{
		cmdtab[i] = ft_gbstrdup(lst->cmd, gb);
		if (!cmdtab[i])
			return (free_and_exit_minish(msh, NULL, EXIT_FAILURE), NULL);
		i++;
		lst = lst->next;
	}
	cmdtab[i] = NULL;
	return (cmdtab);
}
