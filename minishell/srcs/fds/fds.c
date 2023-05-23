/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:45:12 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/23 14:24:41 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_fd_list	*fd_last(t_fd_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	fds_add_back(t_fd_list **lst, t_fd_list *new)
{
	t_fd_list	*tmp;

	if (!lst)
		return ;
	if (*lst)
	{
		tmp = fd_last(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}

t_fd_list	*new_fds()
{
	t_fd_list	*fds;

	fds = malloc(sizeof(t_fd_list));
	fds->in = STDIN_FILENO;
	fds->out = STDOUT_FILENO;
	fds->next = NULL;
	return (fds);
}

void	print_fd(t_fd_list *lst)
{
	t_fd_list	*first;
	int			i;

	first = lst;
	i = 0;
	// printf("lst_fds : ");
	while (lst)
	{
		printf("[%d] ", i);
		printf("in : %-21d | ", lst->in);
		printf("out : %-28d | ", lst->out);
		printf("\n");
		lst = lst->next;
		i++;
	}
	lst = first;
}

t_fd_list	*create_fds_list(t_redir_list *redirs)
{
	t_fd_list		*fds;
	t_fd_list		*new;
	t_redir_list	*first;

	if (redirs)
		fds = new_fds();
	first = redirs;
	while (redirs)
	{
		if (fds->in != STDIN_FILENO)
			close(fds->in);
		if (fds->out != STDOUT_FILENO)
			close(fds->out);
		new = new_fds();
		if (redirs->redir == in)
			new->in = open(redirs->filename, O_RDONLY, 0644);
		// if (redirs->redir == inin)
			// new->in = inin;//HEREDOC
		if (redirs->redir == out)
			new->out = open(redirs->filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (redirs->redir == outout)
			new->out = open(redirs->filename, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (new->in == -1)
			return (perror(redirs->filename), NULL);
		if (new->out == -1)
			return (perror(redirs->filename), NULL);
		fds_add_back(&fds, new);
		redirs = redirs->next;
	}
	redirs = first;
	return (fds);
}