/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:02:59 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/16 18:52:44 by syluiset         ###   ########.fr       */
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
	int i;

	first = lst;
	while (lst)
	{
		i = 0;
		while (lst->cmd[i])
			printf("%s\n", lst->cmd[i]);
		printf("\n");
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

t_cmd_list	*lst_cmd_new(char **content)
{
	t_cmd_list	*new;

	if (!content)
		return (NULL);
	new = malloc(sizeof(t_cmd_list));
	if (!new)
		return (NULL);
	new->cmd = content;
	if (!new->cmd[0])
		return (free(new), NULL);
	new->builtin = false;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

char	**get_cmd(t_word_lst **old_lst)
{
	char		**cmd;
	int 		nb_arg;
	t_word_lst	*next;

	nb_arg = 0;
	cmd = NULL;
	while ((*old_lst)->type != w_pipe)
		nb_arg++;
	cmd = malloc(sizeof(char *) * (nb_arg + 1));
	cmd[nb_arg] = NULL;
	while ((*old_lst) && nb_arg > 0)
	{
		cmd[nb_arg - 1] = ft_strdup((*old_lst)->word);
		nb_arg--;
		next = (*old_lst)->next;
		word_lst_delone(old_lst);
		*old_lst = next;
	}
	return (cmd);
}

t_cmd_list	*create_lst_cmd(t_word_lst **old_lst)
{
	t_cmd_list	*lst;
	t_cmd_list	*new;

	while (*old_lst)
	{
		new = lst_cmd_new(get_cmd(old_lst));
		lst_cmd_add_back(&lst, new);
	}
	print_list(lst);
	return (lst);
}