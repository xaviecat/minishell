/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmdtab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:36:12 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/21 13:47:42 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

char	**create_cmdtab(t_cmd_lst *lst, t_garbage **gb, t_msh *msh)
{
	size_t		i;
	t_cmd_lst	*first;
	char		**cmdtab;

	i = lst_size(lst);
	cmdtab = ft_malloc(gb, sizeof(char *), i + 1);
	if (!cmdtab)
		return (free_and_exit_minish(msh), NULL);
	i = 0;
	lst = first;
	while (lst)
	{
		cmdtab[i] = ft_gbstrdup(lst->cmd, gb);
		if (!cmdtab[i])
			return (free_and_exit_minish(msh), NULL);
		i++;
		lst = lst->next;
	}
	cmdtab[i] = NULL;
	first = lst;
	return (cmdtab);
}
