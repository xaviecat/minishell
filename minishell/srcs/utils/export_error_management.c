/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:10:58 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/21 18:16:27 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	does_contain_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		if (ft_isspace(str[i++]))
			return (1);
	return (0);
}

static int	does_contain_forbidden_char(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	return (1);
}

int	check_for_unexpected_char(t_cmd_lst *cmd)
{
	if (cmd->is_nill == true || does_contain_spaces(cmd->cmd))
		return (printf(MEXP"%s"NOVAL_ID, cmd->cmd), 0);
	if ((*(cmd->cmd) && !ft_isalpha(*(cmd->cmd))) || ((cmd->cmd) + 1
			&& !does_contain_forbidden_char(cmd->cmd + 1)))
		return (printf(MEXP"%s"NOVAL_ID, cmd->cmd), 0);
	return (1);
}

int	export_error_management(t_msh *msh, t_cmd_lst *cmd)
{
	if (!check_for_unexpected_char(cmd))
		return (0);
	(void) msh;
	(void) cmd;
	return (1);
}
