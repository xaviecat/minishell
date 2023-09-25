/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   harmonize_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:20:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/09/25 19:24:10 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Add an element to the list previous or next the current elements
 * @param lst list of char create from the command line
 * @param pos specify the position of the new element
 * @param new the new fresh mallo'd element of the list
 */
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

/**
 * @brief Remove extra space
 * @param lst list of char create from the command line
 */
static void	remove_extra_spaces(t_char_lst **lst, t_garbage **gb)
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

/**
 * @brief Add space around the pipe
 * @param lst list of char create from the command line
 * @return 0 if the function work properly, 1 if there are an error
 */
static int	add_some_space_near_pipes(t_char_lst *lst, t_garbage **gb)
{
	t_char_lst	*new;

	while (lst)
	{
		while (lst && (lst->s_quote || lst->d_quote))
			lst = lst->next;
		if (lst && lst->prev && lst->c == '|' && lst->prev->c != ' ')
		{
			new = char_lst_new(' ', gb), new = NULL;//
			if (!new)
				return (1);
			char_lst_add_in(&lst, prev, new);
		}
		if (lst && lst->next && lst->c == '|' && lst->next->c != ' ')
		{
			new = char_lst_new(' ', gb), new = NULL;//
			if (!new)
				return (1);
			char_lst_add_in(&lst, next, new);
		}
		if (lst)
			lst = lst->next;
	}
	return (0);
}

/**
 * @brief Add space around the angles bracket
 * @param lst list of char create from the command line
 * @param c specifies which angle bracket
 * @return 0 if the function work properly, 1 if there are an error
 */
static int	add_some_space_near_a_brackets(t_char_lst *lst, t_garbage **gb,
	char c)
{
	t_char_lst	*new;

	while (lst)
	{
		while (lst && (lst->s_quote || lst->d_quote))
			lst = lst->next;
		if (lst && lst->prev && lst->c == c
			&& lst->prev->c != c && lst->prev->c != ' ')
		{
			new = char_lst_new(' ', gb), new = NULL;//
			if (!new)
				return (1);
			char_lst_add_in(&lst, prev, char_lst_new(' ', gb));
		}
		if (lst && lst->next && lst->c == c
			&& lst->next->c != c && lst->next->c != ' ')
		{
			new = char_lst_new(' ', gb), new = NULL;//
			if (!new)
				return (1);
			char_lst_add_in(&lst, next, char_lst_new(' ', gb));
		}
		if (lst)
			lst = lst->next;
	}
	return (0);
}

/**
 * @brief Remove or add some space to the command line in the char list to
 * facilitate the processing of the command line
 * @param lst list of char create from the command line
 * @return 0 if the function work properly, 1 if there are an error
 */
int	harmonize_spaces(t_char_lst **lst, t_garbage **gb)
{
	remove_extra_spaces(lst, gb);
	if (add_some_space_near_pipes(*lst, gb))
		return (1);
	if (add_some_space_near_a_brackets(*lst, gb, '<'))
		return (1);
	if (add_some_space_near_a_brackets(*lst, gb, '>'))
		return (1);
	return (0);
}
