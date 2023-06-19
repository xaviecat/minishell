/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:10:58 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/15 23:01:46 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	del_quote_quote(char **str)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (*str[i] && *str[i] != '=')
		i++;
	if (*str[i])
		i++;

}

static int	quote_quote_handling(t_w_cmd_list *cmd)
{
	size_t	i;

	while (cmd)
	{
		i = 0;
		while (cmd->cmd[i] && cmd->cmd[i] != '=')
		{
			if (is_quote_quote(cmd->cmd, i++))
				return (printf(MEXP NOVAL_ID), 0);
		}
		cmd = cmd->next;
		i++;
		while (cmd->cmd[i])
		{
			if (is_quote_quote(cmd->cmd, i))
				return (del_quote_quote(&(cmd->cmd)));
		}
	}
	return (1);
}

int	export_error_management(t_minish *msh, t_w_cmd_list *cmd)
{
	int	error_code;

	error_code = quote_quote_handling(cmd);
	if (error_code <= 0)
		return (error_code);
	(void) msh;
	return (1);
}

//
//
//export $fhsjd banane=test
//
//export
//        $erfs=test
//		banane=test;
//export
//		"=test"
//		"banane=test";
//
//export =test banane="test  youpi";
//
//export =test banane =test NULL ;
