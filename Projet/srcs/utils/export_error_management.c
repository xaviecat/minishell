/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:10:58 by nfaust            #+#    #+#             */
/*   Updated: 2023/09/20 13:48:02 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*trim_plus_sign(char *str, t_garbage **gb)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && !str[i + 1])
			break ;
		i++;
	}
	if (i == ft_strlen(str))
		return (str);
	new_str = ft_malloc(gb, sizeof(char), i + 1);
	if (!new_str)
		return (NULL);
	j = 0;
	while (j++ < i)
		new_str[j - 1] = str[j - 1];
	ft_free(gb, str);
	return (new_str[j - 1] = 0, new_str);
}

static int	verif_first_arg(t_garbage **gb, t_cmd_lst *cmd)
{
	char	**cmd_split;
	int		i;

	i = 0;
	cmd_split = ft_gbsplit(cmd->cmd, '=', gb);
	if (!cmd_split)
		return (0);
	cmd_split[0] = trim_plus_sign(cmd_split[0], gb);
	if (!cmd_split[0])
		return (ft_gbtabfree(cmd_split, gb), 0);
	if (ft_isdigit(cmd_split[0][0]))
		return (ft_gbtabfree(cmd_split, gb),
			printf(MSH E_EXPORT"'%s'%s", cmd->cmd, NT_VAL_ID), 0);
	while (cmd_split[0][i])
	{
		if (!ft_isalnum(cmd_split[0][i]))
		{
			printf(MSH E_EXPORT"'%s'%s", cmd->cmd, NT_VAL_ID);
			return (ft_gbtabfree(cmd_split, gb), 0);
		}
		i++;
	}
	ft_gbtabfree(cmd_split, gb);
	return (1);
}

int	export_error_management(t_msh *msh, t_cmd_lst *cmd)
{
	if (ft_strncmp(cmd->cmd, "=", 2) == 0)
		return (0);
	if (!verif_first_arg(&(msh->garbage), cmd))
		return (0);
	return (1);
}

// ab+ ne doit pas marcher
// ab+= doit marcher
//
