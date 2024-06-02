/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:17:09 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/28 17:27:10 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief free the first node in the garbage collector
 * @param lst
 */
void	ft_free_first(t_garbage **lst)
{
	t_garbage_lst	*first;

	first = NULL;
	first = (*lst)->first->next;
	if (first)
		first->prev = NULL;
	free((*lst)->first->content);
	free((*lst)->first);
	(*lst)->first = first;
}

/**
 * @brief free the last node of the garbage collector
 * @param lst
 */
void	ft_free_last(t_garbage **lst)
{
	t_garbage_lst	*last;

	last = NULL;
	last = (*lst)->last->prev;
	if (last)
		last->next = NULL;
	free((*lst)->last->content);
	free((*lst)->last);
	(*lst)->last = last;
}

/**
 * @brief free a node in the garbage collector
 * @param lst
 */
void	ft_free_other(t_garbage **lst)
{
	t_garbage_lst	*prev;
	t_garbage_lst	*next;

	prev = (*lst)->first->prev;
	next = (*lst)->first->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free((*lst)->first->content);
	free((*lst)->first);
	if (prev)
		(*lst)->first = prev;
	else if (next)
		(*lst)->first = next;
	else
		(*lst)->first = NULL;
	get_first_garbage(lst);
}

/**
 * @brief find and free the node pointed by content
 * @param lst
 * @param content
 */
void	ft_free(t_garbage **lst, void *content)
{
	if (content == NULL)
		return ;
	if (content == (*lst)->first->content)
		return (ft_free_first(lst));
	if (content == (*lst)->last->content)
		return (ft_free_last(lst));
	else
	{
		while ((*lst)->first)
		{
			if ((*lst)->first->content == content)
				return (ft_free_other(lst));
			if ((*lst)->first->next)
				(*lst)->first = (*lst)->first->next;
			else
				break ;
		}
	}
}

/**
 * @brief free all nodes in garbage collector
 * @param lst
 */
void	ft_free_all(t_garbage **lst)
{
	t_garbage_lst	*next;

	next = NULL;
	while ((*lst)->first)
	{
		if ((*lst)->first == (*lst)->last)
			(*lst)->last = NULL;
		if ((*lst)->first->next)
			next = (*lst)->first->next;
		else
			next = NULL;
		free((*lst)->first->content);
		free((*lst)->first);
		if (next)
			next->prev = NULL;
		(*lst)->first = next;
	}
}
