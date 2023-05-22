/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:45:12 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/17 18:38:15 by syluiset         ###   ########.fr       */
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
	return (fds);
}

void    print_fd(t_fd_list *lst)
{
    t_fd_list *first;

    first = lst;
    while (lst)
    {
        printf("%d/%d", lst->out, lst->in);
        lst = lst->next;
    }
    lst = first;
}

t_fd_list	*create_fds_list(t_redir_list *redirs)
{
	t_fd_list		*fds;
	t_fd_list		*new;
	t_redir_list	*first;

	fds = NULL;
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
//		if (redirs->redir == inin)
//			new->in = ;//HEREDOC
		if (redirs->redir == out)
			new->out = open(redirs->filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (redirs->redir == outout)
			new->out = open(redirs->filename, O_RDWR | O_CREAT, O_APPEND, 0777);
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