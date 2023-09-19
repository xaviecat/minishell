/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:10:58 by nfaust            #+#    #+#             */
/*   Updated: 2023/09/20 00:05:01 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	verif_first_arg(t_msh *msh, t_cmd_lst *cmd)
{
	char	**cmd_split;
	int		i;

	i = 0;
	cmd_split = ft_gbsplit(cmd->cmd, '=', &(msh->garbage));
	if (!cmd_split)
		return (0);
	if (ft_isdigit(cmd_split[0][0]))
		return (ft_gbtabfree(cmd_split, &(msh->garbage)), 0);
	while (cmd_split[0][i])
	{
		if (!ft_isalnum(cmd_split[0][i]))
		{
			if (cmd_split[0][i] != '+'
			|| (!cmd_split[0][i + 1] && !cmd_split[1]))
			{
				printf("error char not allowed\n");
				ft_gbtabfree(cmd_split, &(msh->garbage));
				return (0);
			}
		}
		i++;
	}
	ft_gbtabfree(cmd_split, &(msh->garbage));
	return (1);
}

int	export_error_management(t_msh *msh, t_cmd_lst *cmd)
{
	if (ft_strncmp(cmd->cmd, "=", 2) == 0)
		return (0);
	if (!verif_first_arg(msh, cmd))
		return (0);
	return (1);
}

// ab+ ne doit pas marcher
// ab+= doit marcher
//
