/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:16:51 by syluiset          #+#    #+#             */
/*   Updated: 2023/10/03 18:31:32 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief create a new node of type cmd_lst
 * @param w_lst
 * @param s_quote
 * @param d_quote
 * @param gb
 * @return new node with all the content it need
 */
t_cmd_lst	*new_w_cmd_list(t_word_lst *w_lst, bool s_quote, bool d_quote,
			t_garbage **gb)
{
	t_cmd_lst	*new;
	char		*content;

	content = w_lst->word;
	new = ft_malloc(gb, sizeof(t_cmd_lst), 1);
	if (!new)
		return (NULL);
	new->cmd = ft_gbstrtrim(content, " ", gb);
	new->is_nill = w_lst->is_nill;
	if (!new->cmd && errno == ENOMEM)
		return (NULL);
	if (*(new->cmd) == 0)
		new->is_nill = true;
	new->s_quote = s_quote;
	new->d_quote = d_quote;
	new->next = NULL;
	return (new);
}

/**
 * @brief return the last cmd in lst
 * @param lst
 * @return the last cmd
 */
t_cmd_lst	*w_cmd_lst_last(t_cmd_lst *lst)
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
 * @brief get if word is between double or single quote
 * @param old_lst
 * @param two_q
 * @param one_q
 */
void	in_double_or_single(t_word_lst *old_lst, bool *two_q, bool *one_q)
{
	size_t	i;

	i = 0;
	while (old_lst->word[i])
	{
		if (old_lst->word[i] =='"')
			*two_q = true;
		if (old_lst->word[i++] == '\'')
			*one_q = true;
	}
	*two_q = false;
	*one_q = false;
}

t_cmd_lst	*new_splitted_cmd_lst(t_word_lst *old_lst, bool two_quote, bool one_quote, t_garbage **gb)
{
	char		**splitted_word;
	size_t		i;
	t_cmd_lst	*new;

	splitted_word = ft_gbsplit(old_lst->word, ' ', gb);
	if (!splitted_word)
		return (NULL);
	i = 0;
	new = NULL;
	while (splitted_word[i])
	{
		old_lst->word = splitted_word[i];
		if (!new)
		{
			new = new_w_cmd_list(old_lst, one_quote, two_quote, gb);
			new->last_added = new;
		}
		else
		{
			new->last_added->next = new_w_cmd_list(old_lst, one_quote, two_quote, gb);
			new->last_added = new->last_added->next;
		}
		i++;
	}
	return (new);
}

/**
 * @brief create a list of each command (before, between or after pipe)
 * @param old_lst
 * @param gb
 * @return the complete list of command
 */
t_cmd_lst	*get_cmd(t_word_lst **old_lst, t_garbage **gb)
{
	t_cmd_lst	*cmds;
	t_cmd_lst	*new;
	bool		two_quote;
	bool		one_quote;

	cmds = NULL;
	while (*old_lst && (*old_lst)->type != w_pipe)
	{
		if ((*old_lst)->word[0] != '\0')
		{
			in_double_or_single(*old_lst, &two_quote, &one_quote);
			if (two_quote || one_quote)
				new = new_w_cmd_list(*old_lst, one_quote, two_quote, gb);
			else
				new = new_splitted_cmd_lst(*old_lst, one_quote, two_quote, gb);
			if (cmds)
				cmds->last_added->next = new;
			else
				cmds = new;
			cmds->last_added = new;
		}
		word_lst_delone(old_lst, gb);
	}
	return (cmds);
}
