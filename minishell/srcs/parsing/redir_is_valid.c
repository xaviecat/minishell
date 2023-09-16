/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_is_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:14:27 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/26 16:08:26 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	pipe_is_valid(t_word_lst **lst, t_garbage **gb)
{
	while (*lst)
	{
		if ((*lst)->type == w_pipe)
		{
			if (!(*lst)->next || !(*lst)->prev)
			{
				ft_fdprintf(2, RED MSH PIPE_TKN RESET);
				free_error_word_lst(gb, lst);
				return (0);
			}
		}
		if ((*lst)->next)
			*lst = (*lst)->next;
		else
			break ;
	}
	while ((*lst)->prev)
		*lst = (*lst)->prev;
	return (1);
}

int	ft_is_redir(t_type_word type)
{
	if (type == redir || type == hd || type == appnd || type == open_file)
		return (1);
	return (0);
}

int	redir_is_valid(t_word_lst **lst, t_garbage **gb)
{
	while (*lst)
	{
		if (ft_is_redir((*lst)->type))
		{
			if (!(*lst)->next || (*lst)->next->type == w_pipe
				|| ft_is_redir((*lst)->next->type))
			{
				if (!(*lst)->next)
					ft_fdprintf(2, RED MSH NL_TKN RESET);
				else
					ft_fdprintf(2, RED MSH UN_TKN"'%s'\n" RESET,
						(*lst)->next->word);
				free_error_word_lst(gb, lst);
				return (0);
			}
		}
		if ((*lst)->next)
			*lst = (*lst)->next;
		else
			break ;
	}
	while ((*lst)->prev)
		*lst = (*lst)->prev;
	return (1);
}

int	check_pipe_and_redir(t_garbage **gb, t_word_lst **lst)
{
	if (!(redir_is_valid(lst, gb)))
	{
		g_exit_status = 2;
		return (0);
	}
	if (!(pipe_is_valid(lst, gb)))
	{
		g_exit_status = 2;
		return (0);
	}
	return (1);
}
