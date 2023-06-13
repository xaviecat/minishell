/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:39:55 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/12 17:16:37 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief delete one link in the char list
 * @param lst
 */
void	char_lst_delone(t_char_lst **lst, t_garbage **gb)
{
	t_char_lst	*prev;
	t_char_lst	*next;

	prev = (*lst)->prev;
	next = (*lst)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	ft_free(gb, *lst);
	*lst = next;
}

/**
 * @brief create new link for the char list
 * @param c
 * @return the new link
 */
t_char_lst	*char_lst_new(char c, t_garbage **gb)
{
	t_char_lst	*new;

	if (!c)
		return (NULL);
	new = ft_malloc(gb, sizeof(t_char_lst), 1);
	if (!new)
		return (NULL);
	new->c = c;
	new->next = NULL;
	new->prev = NULL;
	new->d_quote = false;
	new->s_quote = false;
	new->pipe = 0;
	new->last_added = NULL;
	return (new);
}

/**
 * @brief find the last link of the char list
 * @param lst
 * @return the last link
 */
t_char_lst	*char_lst_last(t_char_lst *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	free_error_char_lst(t_garbage **gb, t_char_lst **lst_c)
{
	t_char_lst	*next;

	next = NULL;
	while (*lst_c)
	{
		if ((*lst_c)->next)
			next = (*lst_c)->next;
		else
			next = NULL;
		ft_free(gb, *lst_c);
		*lst_c = next;
	}
}

/**
 * @brief split the command char in a char list
 * @param cmd_line
 * @return the char list create
 */
int	create_char_lst_with_c_inside(char *cmd_line, t_minish **sh)
{
	int			i;
	t_char_lst	*new;
	size_t		taille;

	i = 0;
	taille = ft_strlen(cmd_line);
	(void)taille;
	while (cmd_line[i])
	{
		new = char_lst_new(cmd_line[i], &((*sh)->garbage));
		if (!new)
			return (free_error_char_lst(&((*sh)->garbage), &((*sh)->lst_c)), 0);
		if ((*sh)->lst_c)
		{
			new->prev = (*sh)->lst_c->last_added;
			(*sh)->lst_c->last_added->next = new;
		}
		else
			(*sh)->lst_c = new;
		(*sh)->lst_c->last_added = new;
		i++;
	}
	free(cmd_line);
	return (1);
}
