/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:39:55 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/23 17:34:39 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief print all link data
 * @param lst
 */
void	print_lst_char(t_char_lst *lst)
{
	t_char_lst	*first;

	first = lst;
	printf("lst_c :\n");
	while (lst)
	{
		printf("%c | ", lst->c);
		printf("sq : %i | ", lst->s_quote);
		printf("dq : %i | ", lst->d_quote);
		printf("aq : %i | ", lst->a_quote);
		printf("type : %i |", lst->type);
		printf("\n");
		lst = lst->next;
	}
	printf("\n");
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
t_char_lst	*char_lst_new(char c, t_minish **sh)
{
	t_char_lst	*new;

	if (!c)
		return (NULL);
	new = ft_malloc(&(*sh)->garbage, sizeof(t_char_lst), 1);
	if (!new)
		return (NULL); // ! ERROR
	new->c = c;
	new->next = NULL;
	new->prev = NULL;
	new->d_quote = false;
	new->s_quote = false;
	new->a_quote = false;
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
 * @brief split the command char in a char list
 * @param cmd_line
 * @return the char list create
 */
void	create_char_lst_with_c_inside(char *cmd_line, t_minish **sh)
{
	int			i;
	t_char_lst	*new;

	i = 0;
	while (cmd_line[i])
	{
		new = char_lst_new(cmd_line[i], sh);
		if (!new)
			return ;// ! FREE !!!
		if ((*sh)->lst_c->last_added)
		{
			(*sh)->lst_c->last_added->next = new;
			(*sh)->lst_c->last_added = new;
		}
		else
			(*sh)->lst_c = new;
		i++;
	}
}