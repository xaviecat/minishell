/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:02:59 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/07 15:19:46 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void 	free_chunk(t_cmd_list *lst)
{
	while (lst->cmd)
	{
		free(lst->cmd->cmd);
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
	t_w_cmd_list	*first_w;
	int				i;

	i = 0;
	printf(CYAN"lst_cmd:\n");
	while (lst)
	{
		first_w = lst->cmd;
		printf(UNDERLINE"node : %d\n"RESET, i);
		printf(CYAN"builtin : %d\n", lst->builtin);
		printf("cmd :                          | params :\n");
		if (lst->cmd)
		{
			printf("%-30s | ", lst->cmd->cmd);
			lst->cmd = lst->cmd->next;
		}
		else
			printf("(NULL)");
		while (lst->cmd)
		{
			printf("[%s] ", lst->cmd->cmd);
			lst->cmd = lst->cmd->next;
		}
		lst->cmd = first_w;
		printf("\n");
		print_fd(lst->fds);
		print_redir(lst->redirs);
		lst = lst->next;
		i++;
	}
	printf("\n"RESET);
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

	new = ft_malloc(gb, sizeof(t_cmd_list), 1);
	if (!new)
		return (NULL);
	new->cmd = cmds;
//	if (!new->cmd && errno == ENOMEM)
//		return (free(new), NULL);
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
