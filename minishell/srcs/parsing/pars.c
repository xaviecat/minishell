/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:20:00 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/11 18:36:44 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"



//Split apres avoir expand et gerer les redirections
void	split_block_cmd(t_cmd_list **lst) // ? Code d'erreur a faire + retirer quotes ?
{
	t_cmd_list	*first;
	char		*cmd_cp;

	first = *lst;
	while (*lst)
	{
		cmd_cp = ft_strdup((*lst)->cmd[0]);
		if (!cmd_cp)
			break ; // ! ERROR
		ft_free_split((*lst)->cmd);
		(*lst)->cmd = ft_split(cmd_cp, ' ');
		if (!(*lst)->cmd)
			break ; // ! ERROR
		*lst = (*lst)->next;
	}
	*lst = first;
}

t_minish	*parsing_command(char *cmd_line, t_minish *sh)
{
	char	**cmd_splitted;
	int		i;

	cmd_splitted = ft_split(cmd_line, '|');
	sh->cmds = lst_cmd_new(cmd_splitted[0]);
	i = 1;
	while (cmd_splitted[i])
	{
		lst_cmd_add_back(&sh->cmds, lst_cmd_new(cmd_splitted[i]));
		i++;
	}
	//print_list(sh->cmd);
	//expand and open file / heredoc
	split_block_cmd(&sh->cmds);
	return (sh);
}