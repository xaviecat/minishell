/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:39:55 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/16 15:16:42 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief print all link data
 * @param lst
 */
void	print_lst(t_char_lst *lst)
{
	t_char_lst	*first;

	first = lst;
	while (lst)
	{
		printf("%c | ", lst->c);
		printf("sq : %i | ", lst->s_quote);
		printf("dq : %i | ", lst->d_quote);
		printf("aq : %i | ", lst->a_quote);
//		ft_printf("type : %i |", lst->type);
		printf("\n");
		lst = lst->next;
	}
	lst = first;
}

/**
 * @brief delete one link in the char list
 * @param lst
 */
void	char_lst_delone(t_char_lst **lst)
{
	t_char_lst	*prev;
	t_char_lst	*next;

	prev = (*lst)->prev;
	next = (*lst)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(*lst);
	*lst = next;
}

/**
 * @brief create new link for the char list
 * @param c
 * @return the new link
 */
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
	new->s_quote = false;
	new->pipe = 0;
	return (new);
}

/**
 * @brief find the last link of the char list
 * @param lst
 * @return the last link
 */
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

/**
 * @brief add the link new at the end of the char list 'lst'
 * @param lst
 * @param new
 */
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

/**
 * @brief add the link new at the begin of the char list 'lst'
 * @param lst
 * @param new
 */
void	char_lst_add_front(t_char_lst **lst, t_char_lst *new)
{
	new->next = *lst;
	*lst = new;
	return ;
}

/**
 * @brief split the command char in a char list
 * @param cmd_line
 * @return the char list create
 */
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