/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:21:43 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/07 17:59:07 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_redir_list	*new_redir(t_type_redir type_red, t_garbage **gb)
{
	t_redir_list	*red;

	red = ft_malloc(gb, sizeof(t_redir_list), 1);
	if (!red)
	    return (NULL); // ! ERROR maybe free direct ici
	red->redir = type_red;
	red->next = NULL;
	return (red);
}

t_redir_list	*redir_last(t_redir_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	redir_add_back(t_redir_list **lst, t_redir_list *new)
{
	t_redir_list	*tmp;

	if (!lst)
		return ;
	if (*lst)
	{
		tmp = redir_last(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}

void	print_redir(t_redir_list *lst)
{
	t_redir_list	*first;
	int				i;

	first = lst;
	i = 0;
	while (lst)
	{
		printf("[%d] ", i);
		printf("filename : %-15s | ", lst->filename);
		printf("type : %-27d | ", lst->redir);
		printf("\n");
		lst = lst->next;
		i++;
	}
	lst = first;
}

void	free_error_redir(t_garbage **gb, t_redir_list **lst)
{
	t_redir_list	*next;

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

t_redir_list	*get_redir(t_word_lst **lst, t_garbage **gb)
{
	t_redir_list	*redirs;
	t_redir_list	*new;

	redirs = NULL;
	new = NULL;
	while (*lst && (*lst)->type != w_pipe)
	{
	// ! ERROR DE MALLOC A REFLECHIR
		if ((*lst)->type == open_file)
			new = new_redir(in, gb);
		if ((*lst)->type == hd)
			new = new_redir(inin, gb);
		if ((*lst)->type == redir)
			new = new_redir(out, gb);
		if ((*lst)->type == appnd)
			new = new_redir(outout, gb);
		if (new)
		{
			word_lst_delone(lst, gb);
			new->filename = ft_gb_strdup((*lst)->word, gb);
			word_lst_delone(lst, gb);
			redir_add_back(&redirs, new); // ? A voir si il faut le changer
			new = NULL;
		}
		else
		{
			if (errno == ENOMEM)
			{
				free_error_redir(gb, &redirs);
				return (NULL);
			}
			if (!(*lst)->next)
				break ;
			*lst = (*lst)->next;
		}
	}
	*lst = word_lst_first(*lst);
	return (redirs);
}