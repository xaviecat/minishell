/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:02:59 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/11 14:05:21 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void 	free_chunk(t_cmd_list *lst)
{
	int	i;

	i = 0;
	while (lst->cmd[i])
	{
		free(lst->cmd[i]);
		i++;
	}
	free(lst);
}

void 	lst_clear(t_cmd_list **lst)
{
	t_cmd_list	*tmp;
	t_cmd_list	*tmpnext;

	if (!lst)
		return ;
	tmpnext = *lst;
	while (tmpnext != NULL)
	{
		tmp = tmpnext;
		tmpnext = tmp->next;
		free_chunk(tmp);
	}
	*lst = NULL;
	return ;
}

void	print_list(t_cmd_list *lst)
{
	t_cmd_list	*first;

	first = lst;
	while (lst)
	{
		printf("%s\n", lst->cmd[0]);
		lst = lst->next;
	}
	lst = first;
}

t_cmd_list	*lst_cmd_last(t_cmd_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	lst_cmd_add_back(t_cmd_list **lst, t_cmd_list *new)
{
	t_cmd_list	*tmp;

	if (!lst)
		return ;
	if (*lst)
	{
		tmp = lst_cmd_last(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
	return ;
}

t_cmd_list	*lst_cmd_new(char *content)
{
	t_cmd_list	*new;

	if (!content)
		return (NULL);
	new = malloc(sizeof(t_cmd_list));
	if (!new)
		return (NULL);
	new->cmd = malloc(sizeof(char *) * 2);
	new->cmd[0] = ft_strdup(content);
	if (!new->cmd[0])
		return (free(new), NULL);
	new->cmd[1] = NULL;
	new->builtin = false;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}