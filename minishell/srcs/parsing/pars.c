/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:20:00 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/11 14:44:59 by syluiset         ###   ########.fr       */
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
	sh->cmd = lst_cmd_new(cmd_splitted[0]);
	i = 1;
	while (cmd_splitted[i])
	{
		lst_cmd_add_back(&sh->cmd, lst_cmd_new(cmd_splitted[i]));
		i++;
	}
	//print_list(sh->cmd);
	return (sh);
}