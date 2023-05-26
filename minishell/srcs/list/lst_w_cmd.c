/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_w_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:16:51 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/26 15:44:23 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_w_cmd_list	*new_w_cmd_list(char *content, bool s_quote, bool d_quote, t_garbage **gb)
{
	t_w_cmd_list	*new;

	new = ft_malloc(gb, sizeof(t_w_cmd_list), 1);
	if (!new)
		return (NULL); //! ERROR
	new->cmd = ft_gb_strdup(content, gb);
	if (!new->cmd)
		return (NULL);
	new->s_quote = s_quote;
	new->d_quote = d_quote;
	new->next = NULL;
	return (new);
}

t_w_cmd_list	*w_cmd_lst_last(t_w_cmd_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	w_cmd_lst_add_back(t_w_cmd_list **lst, t_w_cmd_list *new)
{
	t_w_cmd_list	*tmp;

	if (!lst)
		return ;
	if (*lst)
	{
		tmp = w_cmd_lst_last(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}

t_w_cmd_list	*get_cmd_2(t_word_lst **old_lst, t_garbage **gb)
{
	t_w_cmd_list	*cmds;
	t_w_cmd_list	*new;
	bool			two_quote;
	bool			one_quote;

    cmds = NULL;
    two_quote = false;
    one_quote = false;
	while (*old_lst && (*old_lst)->type != w_pipe)
	{
		if ((*old_lst)->type == in_d_quote)
            two_quote = true;
        if ((*old_lst)->type == in_s_quote)
            one_quote = true;
		new = new_w_cmd_list((*old_lst)->word,one_quote, two_quote, gb);
        if (cmds)
            cmds->last_added->next = new;
        else
            cmds = new;
        cmds->last_added = new;
        //w_cmd_lst_add_back(&cmds, new);
        word_lst_delone(old_lst, gb);
	}
	return (cmds);
}
