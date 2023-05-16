/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:39:55 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/15 13:24:15 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	print_lst(t_char_lst *lst)
{
	t_char_lst	*first;

	first = lst;
	while (lst)
	{
		ft_printf("%c | ", lst->c);
		ft_printf("sq : %i | ", lst->quote);
		ft_printf("dq : %i | ", lst->d_quote);
//		ft_printf("type : %i |", lst->type);
		ft_printf("\n");
		lst = lst->next;
	}
	lst = first;
}

t_char_lst	*char_lst_new(char c)
{
	t_char_lst	*new;

	if (!c)
		return (NULL);
	new = malloc(sizeof(t_char_lst));
	if (!new)
		return (NULL);
	new->c = c;
	new->next = NULL;
	new->prev = NULL;
	new->d_quote = false;
	new->quote = false;
	new->pipe = 0;
	return (new);
}

t_char_lst	*char_lst_last(t_char_lst *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	char_lst_add_back(t_char_lst **lst, t_char_lst *new)
{
	t_char_lst	*tmp;

	if (!lst)
		return ;
	if (*lst)
	{
		tmp = char_lst_last(*lst);
		new->prev = tmp;
		tmp->next = new;
	}
	else
		*lst = new;
	return ;
}

void	char_lst_add_front(t_char_lst **lst, t_char_lst *new)
{
	new->next = *lst;
	*lst = new;
	return ;
}

t_char_lst	*create_char_lst_with_c_inside(char *cmd_line)
{
	int		i;
	t_char_lst	*lst;
	t_char_lst	*new;

	i = 0;
	lst = NULL;
	while (cmd_line[i])
	{
		new = char_lst_new(cmd_line[i]);
		char_lst_add_back(&lst, new);
		i++;
	}
	return (lst);
}