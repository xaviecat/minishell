/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   harmonize_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:20:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/14 13:28:43 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	char_lst_add_in(t_char_lst **lst, t_position pos, t_char_lst	*new)
{
	t_char_lst	*new_prev;
	t_char_lst	*new_next;

	new->type = space;
	if (pos == prev && *lst)
	{
		new_prev = (*lst)->prev;
		new_next = *lst;
	}
	else
	{
		new_prev = *lst;
		new_next = (*lst)->next;
	}
	new->next = new_next;
	new->prev = new_prev;
	new_prev->next = new;
	new_next->prev = new;
}

void	remove_extra_spaces(t_char_lst **lst, t_garbage **gb)
{
	t_char_lst	*first;

	first = *lst;
	while ((*lst) && ((*lst)->c == ' ' || (*lst)->c == '\t'))
	{
		if ((*lst) == first)
			first = (*lst)->next;
		char_lst_delone(lst, gb);
	}
	while (*lst)
	{
		while ((*lst) && ((*lst)->s_quote || (*lst)->d_quote))
			(*lst) = (*lst)->next;
		while (*lst && (*lst)->next && (*lst)->c == ' '
			&& (*lst)->next->c == ' ')
		{
			if ((*lst) == first)
				first = (*lst)->next;
			char_lst_delone(lst, gb);
		}
		if ((*lst))
			(*lst) = (*lst)->next;
	}
	*lst = first;
}

void	add_some_space_near_pipes(t_char_lst *lst, t_garbage **gb)
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

void	add_some_space_near_a_brackets(t_char_lst *lst, t_garbage **gb, char c)
{
	while (lst)
	{
		while (lst && (lst->s_quote || lst->d_quote))
			lst = lst->next;
		if (lst && lst->prev && lst->c == c
			&& lst->prev->c != c && lst->prev->c != ' ')
			char_lst_add_in(&lst, prev, char_lst_new(' ', gb));
		if (lst && lst->next && lst->c == c
			&& lst->next->c != c && lst->next->c != ' ')
			char_lst_add_in(&lst, next, char_lst_new(' ', gb));
		if (lst)
			lst = lst->next;
	}
}

void	harmonize_spaces(t_char_lst **lst, t_garbage **gb)
{
	remove_extra_spaces(lst, gb);
	add_some_space_near_pipes(*lst, gb);
	add_some_space_near_a_brackets(*lst, gb, '<');
	add_some_space_near_a_brackets(*lst, gb, '>');
}
