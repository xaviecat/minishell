/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_word_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:12:14 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/12 17:14:07 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief create a new link for a word list
 * @param word
 * @return the new link created
 */
t_word_lst	*word_lst_new(char *word, t_garbage **gb)
{
	t_word_lst	*new;

	if (!word)
		return (NULL);
	new = ft_malloc(gb, sizeof(t_word_lst), 1);
	if (!new)
		return (NULL);
	new->word = ft_gbstrdup(word, gb);
	new->type = not_define;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/**
 * @brief delete one link in the word list
 * @param lst
 */
void	word_lst_delone(t_word_lst **lst, t_garbage **gb)
{
	t_word_lst	*prev;
	t_word_lst	*next;

	prev = (*lst)->prev;
	next = (*lst)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	ft_free(gb, (*lst)->word);
	ft_free(gb, *lst);
	if (next)
		*lst = next;
	else
		*lst = prev;
}

t_word_lst	*word_lst_first(t_word_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!lst->prev)
			return (lst);
		lst = lst->prev;
	}
	return (lst);
}
