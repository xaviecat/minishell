/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:02:59 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/23 11:57:53 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void 	free_chunk(t_cmd_list *lst)
{
	while (lst->cmd)
	{
		free(lst->cmd);
        lst->cmd = lst->cmd->next;
	}
	free(lst);
}

void	lst_clear(t_cmd_list **lst)
{
	t_cmd_list	*tmp;
	t_cmd_list	*tmpnext;

	if (!lst)
		return ;
	tmpnext = *lst;
	while (tmpnext != NULL)
	{
		tmp = tmpnext;
		tmpnext = tmp->next;
		free_chunk(tmp);
	}
	*lst = NULL;
	return ;
}

void	print_lst_cmd(t_cmd_list *lst)
{
	t_cmd_list		*first;
	t_w_cmd_list	*first_w;

	first = lst;
	first_w = lst->cmd;
	while (lst)
	{
		printf("the command :");
		printf("%s ", lst->cmd->cmd);
		printf("\n");
		lst->cmd = lst->cmd->next;
		while (lst->cmd)
		{
			printf("parameters :");
			printf("%s ", lst->cmd->cmd);
			printf("\n");
			lst->cmd = lst->cmd->next;
		}

		printf("\n is a builtin : %d\n", lst->builtin);
		print_redir(lst->redirs);
		print_fd(lst->fds);
		printf("\n\n");
		lst = lst->next;
	}
	lst = first;
	lst->cmd = first_w;
}

t_cmd_list	*lst_cmd_last(t_cmd_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	lst_cmd_add_back(t_cmd_list **lst, t_cmd_list *new)
{
	t_cmd_list	*tmp;

	if (!lst)
		return ;
	if (*lst)
	{
		tmp = lst_cmd_last(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}

t_cmd_list	*lst_cmd_new(t_w_cmd_list *cmds, t_fd_list *fds, t_redir_list *redir, t_garbage **gb)
{
	t_cmd_list	*new;

	if (!cmds)
		return (NULL);
	new = ft_malloc(gb, sizeof(t_cmd_list), 1);
	if (!new)
		return (NULL);
	new->cmd = cmds;
	if (!new->cmd)
		return (free(new), NULL);
	new->builtin = false;
	new->redirs = redir;
	new->fds = fds;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

/**
 * @brief count number of arg, in fact the number of string the tab of cmd
 * should need
 * @param lst
 * @param next
 * @return the number of arg
 */
int	get_number_of_arg(t_word_lst **lst, t_word_lst **next)
{
	int	nb_arg;

	nb_arg = 0;
	while (*lst && (*lst)->type != w_pipe)
	{
		nb_arg++;
		if ((*lst)->next)
			*lst = (*lst)->next;
		else
		{
			*next = NULL;
			break ;
		}
	}
	return (nb_arg);
}

bool	builtin_or_command(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (true);
	return (false);
}


//t_cmd_list	*create_lst_cmd(t_word_lst **old_lst, t_fd_list *fds, t_redir_list *redirs)
//{
//	t_cmd_list	*lst;
//	t_cmd_list	*new;
//
//	lst = NULL;
//	while (*old_lst && (*old_lst)->type != w_pipe)
//	{
//		new = lst_cmd_new(get_cmd(old_lst), builtin_or_command(*old_lst));
//	}
//	return (lst);
//}
