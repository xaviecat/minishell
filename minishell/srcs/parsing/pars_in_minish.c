/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_in_minish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:50:54 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/22 13:53:58 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

//void	open_outfile_and_infile(t_word_lst **lst, t_minish **minish)
//{
//	if ((*lst)->type == infile)
//	{
//		if ((*minish)->infile != STDIN_FILENO)
//			close((*minish)->infile); // A VOIR SI ON DOIT LE FAIRE AVANT OU APRES AVOIR TESTER L'OUVERTURE DU NEW
//		(*minish)->infile = open((*lst)->word, O_RDONLY, 0644);
//		if (infile == -1)
//		{
//			perror((*lst)->word);
//			return; // ! ERROR
//		}
//		word_lst_delone(lst);
//	}
//	if ((*lst)->type == outfile)
//	{
//		if ((*minish)->outfile != STDOUT_FILENO)
//			close((*minish)->outfile); // A VOIR SI ON DOIT LE FAIRE AVANT OU APRES AVOIR TESTER L'OUVERTURE DU NEW
//		if ((*lst)->prev->type == redir)
//		{
//			(*minish)->outfile = open((*lst)->word, O_RDWR | O_CREAT | O_TRUNC, 0777);
//			if (outfile == -1)
//			{
//				perror((*lst)->word);
//				return; // ! ERROR
//			}
//		}
//		if ((*lst)->prev->type == appnd)
//		{
//			(*minish)->outfile = open((*lst)->word, O_RDWR | O_CREAT, O_APPEND, 0777);
//			if (outfile == -1)
//			{
//				perror((*lst)->word);
//				return; // ! ERROR
//			}
//		}
//		word_lst_delone(lst);
//	}
//}

void	sh_pars(t_word_lst **old_lst, t_minish **minish)
{
	t_redir_list	*redirs;
	t_fd_list		*fds;
	t_cmd_list		*new;

	redirs = NULL;
	fds = NULL;
	new = NULL;
	while (*old_lst)
	{
		redirs = get_redir(old_lst);
		fds = create_fds_list(redirs);
		new = lst_cmd_new(get_cmd(old_lst), fds, redirs);
		new->builtin = builtin_or_command(new->cmd[0]);
		lst_cmd_add_back(&(*minish)->cmds, new);
	}
}