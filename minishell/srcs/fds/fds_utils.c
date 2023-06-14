/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:23:46 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/14 14:23:46 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	fds_add_back(t_fd_list **lst, t_fd_list *new)
{
	if (!lst)
		return ;
	if ((*lst)->last_added)
		(*lst)->last_added->next = new;
	else
		*lst = new;
	(*lst)->last_added = new;
}

t_fd_list	*new_fds(t_garbage **gb)
{
	t_fd_list	*fds;

	fds = ft_malloc(gb, sizeof(t_fd_list), 1);
	if (!fds)
		return (NULL);
	fds->in = STDIN_FILENO;
	fds->out = STDOUT_FILENO;
	fds->next = NULL;
	fds->last_added = NULL;
	return (fds);
}

void	free_error_fds(t_garbage **gb, t_fd_list **lst)
{
	t_fd_list	*next;

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
