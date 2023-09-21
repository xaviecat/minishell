/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmdtab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:36:12 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/21 16:04:27 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	count_length_tab(t_cmd_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

/**
 * @brief create the tab with all command in lst
 * @param lst
 * @param gb
 * @param msh
 * @return the cmdtab newly create
 */
char	**create_cmdtab(t_cmd_lst *lst, t_garbage **gb, t_msh *msh)
{
	size_t		i;
	char		**cmdtab;

	i = count_length_tab(lst);
	cmdtab = ft_malloc(gb, sizeof(char *), i + 1);
	if (!cmdtab)
		return (free_and_exit_minish(msh), NULL);
	i = 0;
	while (lst)
	{
		cmdtab[i] = ft_gbstrdup(lst->cmd, gb);
		if (!cmdtab[i])
			return (free_and_exit_minish(msh), NULL);
		i++;
		lst = lst->next;
	}
	cmdtab[i] = NULL;
	return (cmdtab);
}
