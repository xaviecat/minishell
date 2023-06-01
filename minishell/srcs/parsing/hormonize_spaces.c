/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hormonize_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:20:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/31 11:11:04 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	char_lst_add_in(t_char_lst **lst, t_position pos, t_char_lst	*new) //! securiser en cas de debut ou de fin de luiste
{
	t_char_lst	*new_prev;
	t_char_lst	*new_next;

	if (pos == prev && *lst)
	{
		new_prev = (*lst)->prev;
		new_next = *lst;
		// new->prev = (*lst)->prev;
		// new->next = *lst;
		// (*lst)->prev = new;
		// (*lst)->prev->next = new;
	}
	else if (pos == next && *lst)
	{
		new_prev = *lst;
		new_next = (*lst)->next;
		// new->prev = (*lst);
		// new->next = (*lst)->next;
		// (*lst)->next = new;
		// (*lst)->next->prev = new;
	}
	new->next = new_next;
	new->prev = new_prev;
	new_prev->next = new;
	new_next->prev = new;
}

void	remove_extra_spaces(t_char_lst *lst, t_garbage **gb)
{
	while (lst)
	{
		while (lst && (lst->s_quote || lst->d_quote))
			lst = lst->next;
		while (lst && lst->c == ' ' && lst->next->c == ' ')
			char_lst_delone(&lst, gb);
		if (lst)
			lst = lst->next;
	}
}

void	add_some_spaces(t_char_lst *lst, t_garbage **gb)
{
	while (lst)
	{
		while (lst && (lst->s_quote || lst->d_quote))
			lst = lst->next;
		if (lst && lst->prev && lst->c == '|' && lst->prev->c != ' ')
			char_lst_add_in(&lst, prev, char_lst_new(' ', gb));
		if (lst && lst->next && lst->c == '|' && lst->next->c != ' ')
			char_lst_add_in(&lst, next, char_lst_new(' ', gb));
		if (lst)
			lst = lst->next;
	}
}

void	harmonize_spaces(t_char_lst *lst, t_garbage **gb)
{
	remove_extra_spaces(lst, gb);
	add_some_spaces(lst, gb);
}

/*
 *
 * tant que je ne suis pas entre quotes
 	*
*
 *
 *
 *
 * salut| cat
 * salut|
 *
 *
 *
 *
 *
 * echo hello world > salut| cat salut    |   echo "                  salut                   "
 * echo hello world > salut| cat -en |cat salut|echo "|sal|ut| |"
 */