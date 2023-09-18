/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:16:51 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/19 14:04:01 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
	printf("{%d}\n", w_lst->is_nill);
	if (!new->cmd && errno == ENOMEM)
		return (NULL);
	if (*(new->cmd) == 0)
		new->is_nill = true;
	new->s_quote = s_quote;
	new->d_quote = d_quote;
	new->next = NULL;
	return (new);
}

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

t_cmd_lst	*get_cmd(t_word_lst **old_lst, t_garbage **gb)
{
	t_cmd_lst	*cmds;
	t_cmd_lst	*new;
	bool		two_quote;
	bool		one_quote;

	cmds = NULL;
	two_quote = false;
	one_quote = false;
	while (*old_lst && (*old_lst)->type != w_pipe)
	{
		if (!((*old_lst)->word[0] == '\0'))
		{
			if ((*old_lst)->type == in_d_quote)
				two_quote = true;
			if ((*old_lst)->type == in_s_quote)
				one_quote = true;
			new = new_w_cmd_list(*old_lst, one_quote, two_quote, gb);
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
