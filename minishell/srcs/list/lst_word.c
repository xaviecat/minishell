/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:00:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/16 14:27:28 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*reforme_word(t_char_lst **lst_c)
{
	char		*word;
	int			nb_c_word;
	t_char_lst	*prev;
	t_char_lst	*next;

	nb_c_word = 0;
	while (*lst_c != NULL && (*lst_c)->type != space)
	{
		nb_c_word++;
		if ((*lst_c)->next)
			*lst_c = (*lst_c)->next;
		else
		{
			next = NULL;
			break;
		}
	}
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

int	get_cat_of_word(char *word)
{
	if (ft_strncmp(word , "<", 2) == 0)
		return (open_file);
	if (ft_strncmp(word, "<<", 3) == 0)
		return (hd);
	if (ft_strncmp(word, ">", 2) == 0)
		return (redir);
	if (ft_strncmp(word, ">>", 3) == 0)
		return (appnd);
	if (ft_strncmp(word, "-", 1) == 0)
		return (param);
	if (ft_strncmp(word, "|", 1) == 0)
		return (w_pipe);
	if (ft_strchr(word, '$') != NULL)
		return (expand);
	return (not_define);
}

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

void	word_lst_add_front(t_word_lst **lst, t_word_lst *new)
{
	new->next = *lst;
	*lst = new;
	return ;
}

int		is_a_bultin(char *word)
{
	if (strncmp(word, "exit", 5) == 0)
		return (builtin);
	if (strncmp(word, "echo", 5) == 0)
		return (builtin);
	if (strncmp(word, "cd", 3) == 0)
		return (builtin);
	if (strncmp(word, "pwd", 4) == 0)
		return (builtin);
	if (strncmp(word, "export", 7) == 0)
		return (builtin);
	if (strncmp(word, "unset", 6) == 0)
		return (builtin);
	if (strncmp(word, "env", 4) == 0)
		return (builtin);
	return (command);
}

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
			if ((*lst)->prev->type == not_define)
				is_a_bultin((*lst)->word);
		}
		*lst = (*lst)->next;
	}
	*lst = first;
}

void	print_lst_w(t_word_lst *lst)
{
	t_word_lst	*first;

	first = lst;
	while (lst)
	{
		printf("%s/%d/%p\n", lst->word, lst->type, lst->next);
		lst = lst->next;
	}
	lst = first;
}

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