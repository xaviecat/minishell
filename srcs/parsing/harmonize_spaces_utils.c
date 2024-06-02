/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   harmonize_spaces_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:48:48 by xcharra           #+#    #+#             */
/*   Updated: 2023/10/03 13:33:08 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Add an element to the list previous or next the current elements
 * @param lst current element in the list of char create from the command line
 * @param pos specify the position of the new element
 * @param new the new fresh malloc'd element of the list
 */
static void	char_lst_add_in(t_char_lst **lst, t_position pos, t_char_lst *new)
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
 * @brief Add space before or after the current element in the list of char
 * @param lst current element in the list of char create from the command line
 * @param pos Specify where add the new element
 * @return 0 if the function work properly, 1 if there are an error
 */
int	add_space(t_char_lst *lst, t_position pos, t_garbage **gb)
{
	t_char_lst	*new;

	new = char_lst_new(' ', gb);
	if (!new)
		return (1);
	char_lst_add_in(&lst, pos, new);
	return (0);
}
