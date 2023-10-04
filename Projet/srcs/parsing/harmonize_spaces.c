/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   harmonize_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:20:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/10/03 13:33:06 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
	while (lst)
	{
		while (lst && (lst->s_quote || lst->d_quote))
			lst = lst->next;
		if (lst && lst->prev && lst->c == '|' && lst->prev->c != ' ')
			if (add_space(lst, prev, gb))
				return (1);
		if (lst && lst->next && lst->c == '|' && lst->next->c != ' ')
			if (add_space(lst, next, gb))
				return (1);
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
	while (lst)
	{
		while (lst && (lst->s_quote || lst->d_quote))
			lst = lst->next;
		if (lst && lst->prev && lst->c == c
			&& lst->prev->c != c && lst->prev->c != ' ')
			if (add_space(lst, prev, gb))
				return (1);
		if (lst && lst->next && lst->c == c
			&& lst->next->c != c && lst->next->c != ' ')
			if (add_space(lst, next, gb))
				return (1);
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
