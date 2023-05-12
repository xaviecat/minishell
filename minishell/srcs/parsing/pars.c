/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:20:00 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/11 18:36:44 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	**parsing_argu(char *arg_term)
{
	char	**arg;

	arg = ft_split(arg_term, ' ');
	return (arg);
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
	return (sh);
}