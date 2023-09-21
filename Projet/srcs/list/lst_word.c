/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:00:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/21 15:28:17 by syluiset         ###   ########.fr       */
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

/**
 * @brief free all the list
 * @param gb
 * @param lst
 */
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
 * @brief reforme the word and give all content needed by new
 * @param new
 * @param sh
 * @return 1 if is there an error, 0 otherwise
 */
static int	get_new_word(t_word_lst **new, t_msh *sh)
{
	char	*word;
	bool	in_s_quote;
	bool	in_d_quote;

	word = NULL;
	in_s_quote = sh->lst_c->s_quote;
	in_d_quote = sh->lst_c->d_quote;
	word = reforme_word(&sh, &(sh->garbage));
	*new = word_lst_new(word, &(sh->garbage));
	if (!*new)
		return (free_error_word_lst(&(sh->garbage), &(sh->lst_w)), 1);
	(*new)->type = get_cat_of_word((*new)->word);
	(*new)->in_s_quote = in_s_quote;
	(*new)->in_d_quote = in_d_quote;
	return (0);
}

/**
 * @brief create a word list based on the char list pass in parameter
 * @param old_lst
 * @return the word list created
 */
int	create_word_lst(t_msh **sh)
{
	t_word_lst	*new;

	if (!(*sh)->lst_c)
		return (2);
	while ((*sh)->lst_c)
	{
		if (get_new_word(&new, *sh))
			return (1);
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
	return (0);
}
