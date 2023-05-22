/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_w_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:16:51 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/22 17:36:52 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_w_cmd_list	*new_w_cmd_list(char *content, bool s_quote, bool d_quote)
{
	t_w_cmd_list	*new;

	new = malloc(sizeof(t_w_cmd_list));
	if (!new)
		return (NULL); //! ERROR
	new->cmd = ft_strdup(content);
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

//t_w_cmd_list	*get_cmd_2(t_word_lst **old_lst)
//{
//	t_w_cmd_list	*cmds;
//	t_w_cmd_list	*new;
//	bool			in_d_quote;
//	bool			in_s_quote;
//
//	while (*old_lst)
//	{
//		if
//		new = new_w_cmd_list((*old_lst)->word, (*old_lst)->)
//	}
//}
