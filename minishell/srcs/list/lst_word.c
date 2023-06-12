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
	//int	i;

//	i = 0;
	nb_c_word = 0;
	while (*lst_c)
	{
		if ((*lst_c)->next && (*lst_c)->type == space \
		&& ((*lst_c)->d_quote == false && (*lst_c)->s_quote == false))
			break;
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
char	*reforme_word(t_minish **sh, t_garbage **gb)
{
	char		*word;
	int			nb_c_word;
	int			i;

	i = 0;
	nb_c_word = get_number_c_of_word(&(*sh)->lst_c);
	word = ft_malloc(gb, 1 ,nb_c_word + 1);
	if (!word)
		return (NULL); // ! ERROR
	while ((*sh)->lst_c != NULL && i < nb_c_word)
	{
	    //dprintf(2, "%c/", (*sh)->lst_c->c);
		word[i] = (*sh)->lst_c->c;
		//dprintf(2,"%p/", (*sh)->lst_c);
		char_lst_delone(&(*sh)->lst_c, gb);
		//(*sh)->lst_c = (*sh)->lst_c->next;
		i++;
	}
	word[i] = '\0';
	if ((*sh)->lst_c && (*sh)->lst_c->type == space) // ? voir si on doit verifier que next n'est pas null
		char_lst_delone(&(*sh)->lst_c, gb);
	return (word);
}

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
void	print_lst_word(t_word_lst *lst)
{
	t_word_lst	*first;

	first = lst;
	printf(LBLUE"lst_w:\n");
	while (lst)
	{
		printf("%-30s | ", lst->word);
		printf("type : %-2d | ", lst->type);
		// printf("next : %p |", lst->next);
		printf("\n");
		lst = lst->next;
	}
	printf("\n"RESET);
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
int	create_word_lst(t_minish **sh)
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
		{
			free_error_word_lst(&((*sh)->garbage), &((*sh)->lst_w));
			return (0);
		}
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