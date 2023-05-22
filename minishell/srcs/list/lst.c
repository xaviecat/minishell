/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:02:59 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/22 13:52:27 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void 	free_chunk(t_cmd_list *lst)
{
	int	i;

	i = 0;
	while (lst->cmd[i])
	{
		free(lst->cmd[i]);
		i++;
	}
	free(lst);
}

void 	lst_clear(t_cmd_list **lst)
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

void	print_list(t_cmd_list *lst)
{
	t_cmd_list	*first;
	int i;

	first = lst;
	while (lst)
	{
		i = 0;
		while (lst->cmd[i])
		{
			printf("the command :");
			printf("%s ", lst->cmd[i]);
			i++;
		}
		printf("\n is a builtin : %d\n", lst->builtin);
        print_redir(lst->redirs);
        print_fd(lst->fds);
		printf("\n\n");
		lst = lst->next;
	}
	lst = first;
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

t_cmd_list	*lst_cmd_new(char **content, t_fd_list *fds, t_redir_list *redir)
{
	t_cmd_list	*new;

	printf("new : %s\n", content[0]);
	if (!content)
		return (NULL);
	new = malloc(sizeof(t_cmd_list));
	if (!new)
		return (NULL);
	new->cmd = content;
	if (!new->cmd[0])
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

char	**get_cmd(t_word_lst **old_lst)
{
	char		**cmd;
	int 		nb_arg;
	t_word_lst	*prev;
	t_word_lst	*next;

	nb_arg = get_number_of_arg(old_lst, &next);
	cmd = NULL;
	cmd = malloc(sizeof(char *) * (nb_arg + 1));
	cmd[nb_arg] = NULL;
    if (*old_lst && (*old_lst)->type == w_pipe && (*old_lst)->prev != NULL)
	{
		prev = (*old_lst)->prev;
		word_lst_delone(old_lst);
		*old_lst = prev;
		next = (*old_lst)->next;
	}
	while ((*old_lst) && nb_arg > 0)
	{
	    printf("%s\n", (*old_lst)->word);
		cmd[nb_arg - 1] = ft_strdup((*old_lst)->word);
		nb_arg--;
		prev = (*old_lst)->prev;
		word_lst_delone(old_lst);
		*old_lst = prev;
	}
	*old_lst = next;
	return (cmd);
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
