/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:00:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/22 15:04:56 by syluiset         ###   ########.fr       */
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
int	get_number_c_of_word(t_char_lst **lst_c, t_char_lst **next)
{
	int	nb_c_word;

	nb_c_word = 0;
	while (*lst_c)
	{
		if ((*lst_c)->type == space && ((*lst_c)->d_quote == false \
		&& (*lst_c)->s_quote == false))
			break;
		nb_c_word++;
		if ((*lst_c)->next)
			*lst_c = (*lst_c)->next;
		else
		{
			*next = NULL;
			break ;
		}
	}
	return (nb_c_word);
}

/**
 * @brief create a word with the character of the char list
 * since we found a space type
 * @param lst_c
 * @return the word created
 */
char	*reforme_word(t_char_lst **lst_c)
{
	char		*word;
	int			nb_c_word;
	t_char_lst	*prev;
	t_char_lst	*next;

	nb_c_word = get_number_c_of_word(lst_c, &next);
	word = ft_calloc(nb_c_word + 1, sizeof(char));
	if (!word)
		return (NULL); // ! ERROR
	if (*lst_c && (*lst_c)->type == space && (*lst_c)->prev != NULL)
	{
		prev = (*lst_c)->prev;
		char_lst_delone(lst_c);
		*lst_c = prev;
		next = (*lst_c)->next;
	}
	while (*lst_c != NULL && nb_c_word-- >= 0)
	{
		word[nb_c_word] = (*lst_c)->c;
		prev = (*lst_c)->prev;
		char_lst_delone(lst_c);
		(*lst_c) = prev;
	}
	*lst_c = next;
	return (word);
}

/**
 * @brief create a new link for a word list
 * @param word
 * @return the new link created
 */
t_word_lst	*word_lst_new(char *word)
{
	t_word_lst	*new;

	if (!word)
		return (NULL);
	new = malloc(sizeof(t_word_lst));
	if (!new)
		return (NULL);
	new->word = ft_strdup(word);
	free(word);
	new->type = not_define;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/**
 * @brief find the last link in the word list
 * @param lst
 * @return the last link
 */
t_word_lst	*word_lst_last(t_word_lst *lst)
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
 * @brief delete one link in the word list
 * @param lst
 */
void	word_lst_delone(t_word_lst **lst)
{
	t_word_lst	*prev;
	t_word_lst	*next;

	prev = (*lst)->prev;
	next = (*lst)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(*lst);
	if (next)
		*lst = next;
	else
		*lst = prev;
}
/**
 * @brief add the new link at the back of the word list 'lst'
 * @param lst
 * @param new
 */
void	word_lst_add_back(t_word_lst **lst, t_word_lst *new)
{
	t_word_lst	*tmp;

	if (!lst)
		return ;
	if (*lst)
	{
		tmp = word_lst_last(*lst);
		new->prev = tmp;
		tmp->next = new;
	}
	else
		*lst = new;
	return ;
}

/**
 * @brief add the new link at the front of the word list 'lst'
 * @param lst
 * @param new
 */
void	word_lst_add_front(t_word_lst **lst, t_word_lst *new)
{
	new->next = *lst;
	*lst = new;
	return ;
}

/**
 * @brief assign a type to the link pass in parameter
 * @param lst
 */
void	get_other_type_word(t_word_lst **lst)
{
	t_word_lst	*first;

	first = *lst;
	while (*lst)
	{
		if ((*lst)->prev && (*lst)->type == not_define)
		{
			if ((*lst)->prev->type == redir)
				(*lst)->type = outfile;
			if ((*lst)->prev->type == hd)
				(*lst)->type = delimiteur;
			if ((*lst)->prev->type == appnd)
				(*lst)->type = outfile;
			if ((*lst)->prev->type == open_file)
				(*lst)->type = infile;
		}
		if ((*lst)->type == not_define)
			(*lst)->type = is_a_bultin((*lst)->word);
		*lst = (*lst)->next;
	}
	*lst = first;
}

/**
 * @brief print all the word list pass in parameter
 * @param lst
 */
void	print_lst_w(t_word_lst *lst)
{
	t_word_lst	*first;

	first = lst;
	while (lst)
	{
		printf("%s/%d/%p\n", lst->word, lst->type, lst->next);
		lst = lst->next;
	}
	printf("\n");
	lst = first;
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
/**
 * @brief create a word list based on the char list pass in parameter
 * @param old_lst
 * @return the word list created
 */
t_word_lst	*create_word_lst(t_char_lst *old_lst)
{
	t_word_lst	*lst;
	t_word_lst	*new;
	char		*word;

	lst = NULL;
	while (old_lst)
	{
		word = reforme_word(&old_lst);
		new = word_lst_new(word);
		new->type = get_cat_of_word(new->word);
		word_lst_add_back(&lst, new);
	}
	get_other_type_word(&lst);
	return (lst);
}
