/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:00:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/05 11:48:36 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief count the length of the word, in fact it
 * count since it find a space type
 * @param lst_c
 * @param next
 * @return the length of the word
 */
int	get_number_c_of_word(t_char_lst **lst_c)
{
	int	nb_c_word;

	nb_c_word = 0;
	while (*lst_c)
	{
		if ((*lst_c)->next && (*lst_c)->type == space \
		&& ((*lst_c)->d_quote == false && (*lst_c)->s_quote == false))
			break ;
		nb_c_word++;
		if ((*lst_c)->next)
			*lst_c = (*lst_c)->next;
		else
			break ;
	}
	while ((*lst_c)->prev)
		*lst_c = (*lst_c)->prev;
	return (nb_c_word);
}

/**
 * @brief create a word with the character of the char list
 * since we found a space type
 * @param lst_c
 * @return the word created
 */
char	*reforme_word(t_msh **sh, t_garbage **gb)
{
	char		*word;
	int			nb_c_word;
	int			i;

	i = 0;
	nb_c_word = get_number_c_of_word(&(*sh)->lst_c);
	word = ft_malloc(gb, 1, nb_c_word + 1);
	if (!word)
		return (NULL);
	while ((*sh)->lst_c != NULL && i < nb_c_word)
	{
		word[i] = (*sh)->lst_c->c;
		char_lst_delone(&(*sh)->lst_c, gb);
		i++;
	}
	word[i] = '\0';
	if ((*sh)->lst_c && (*sh)->lst_c->type == space)
		char_lst_delone(&(*sh)->lst_c, gb);
	return (word);
}

void	free_error_word_lst(t_garbage **gb, t_word_lst **lst)
{
	t_word_lst	*next;

	next = NULL;
	while (*lst)
	{
		if ((*lst)->next)
			next = (*lst)->next;
		else
			next = NULL;
		ft_free(gb, *lst);
		*lst = next;
	}
}

/**
 * @brief create a word list based on the char list pass in parameter
 * @param old_lst
 * @return the word list created
 */
int	create_word_lst(t_msh **sh)
{
	t_word_lst	*new;
	char		*word;

	if (!(*sh)->lst_c)
		return (0);
	while ((*sh)->lst_c)
	{
		word = NULL;
		word = reforme_word(sh, &((*sh)->garbage));
		new = word_lst_new(word, &((*sh)->garbage));
		if (!new)
			return (free_error_word_lst(&((*sh)->garbage), &((*sh)->lst_w)), 0);
		new->type = get_cat_of_word(new->word);
		if ((*sh)->lst_w)
		{
			new->prev = (*sh)->lst_w->last_added;
			(*sh)->lst_w->last_added->next = new;
		}
		else
			(*sh)->lst_w = new;
		(*sh)->lst_w->last_added = new;
	}
	get_other_type_word(&(*sh)->lst_w);
	return (1);
}
