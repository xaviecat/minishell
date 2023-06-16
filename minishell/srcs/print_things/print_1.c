/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:54:48 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/15 17:18:26 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	print_fd(t_fd_lst *lst)
{
	int			i;

	i = 0;
	while (lst)
	{
		printf("[%d] ", i);
		printf("in : %-21d | ", lst->in);
		printf("out : %-28d | ", lst->out);
		printf("\n");
		lst = lst->next;
		i++;
	}
}

void	print_redir(t_redir_lst *lst)
{
	int				i;

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
}

/**
 * @brief print all link data
 * @param lst
 */
void	print_lst_char(t_char_lst *lst)
{
	printf(BLUE"lst_c :\n");
	while (lst)
	{
		printf("%c | ", lst->c);
		printf("sq : %i | ", lst->s_quote);
		printf("dq : %i | ", lst->d_quote);
		printf("type : %i |", lst->type);
		printf("\n");
		lst = lst->next;
	}
	printf("\n"RESET);
}

/**
 * @brief print all the word list pass in parameter
 * @param lst
 */
void	print_lst_word(t_word_lst *lst)
{
	printf(LBLUE"lst_w:\n");
	while (lst)
	{
		printf("%-30s | ", lst->word);
		printf("type : %-2d | ", lst->type);
		printf("\n");
		lst = lst->next;
	}
	printf("\n"RESET);
}

void	print_tab(char **tabi)
{
	int	i;

	i = 0;
	while (tabi[i])
	{
		printf("%s\n", tabi[i]);
		i++;
	}
}

void	print_lst_cmd(t_node_lst *lst)
{
	t_cmd_lst		*first_w;
	int				i;

	i = 0;
	printf(CYAN"lst_cmd:\n");
	while (lst)
	{
		first_w = lst->lst_cmd;
		printf(UNDERLINE"node : %d\n"RESET, i);
		printf(CYAN"builtin : %d\n", lst->builtin);
		printf("cmd :                          | params :\n");
		if (lst->lst_cmd)
		{
			printf("%-30s | ", lst->lst_cmd->cmd);
			lst->lst_cmd = lst->lst_cmd->next;
		}
		else
			printf("(null)                         |");
		while (lst->lst_cmd)
		{
			printf("[%s] ", lst->lst_cmd->cmd);
			lst->lst_cmd = lst->lst_cmd->next;
		}
		if (lst->cmdpath)
			printf("\ncmdpath : %s", lst->cmdpath);
		lst->lst_cmd = first_w;
		printf(CYAN"\n");
		print_fd(lst->fds);
		print_redir(lst->redirs);
		lst = lst->next;
		i++;
	}
	printf(RESET"\n");
}
