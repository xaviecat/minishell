/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:10:58 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/04 15:36:00 by nfaust           ###   ########.fr       */
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

int	check_concat(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

static int	verif_first_arg(t_garbage **gb, t_cmd_lst *cmd)
{
	char	**cmd_split;
	int		i;

	i = 0;
	cmd_split = ft_gbsplit(cmd->cmd, '=', gb);
	if (!cmd_split)
		return (0);
	if (check_concat(cmd->cmd))
		cmd_split[0] = trim_plus_sign(cmd_split[0], gb);
	if (!cmd_split[0])
		return (ft_gbtabfree(cmd_split, gb), 0);
	if (ft_isdigit(cmd_split[0][0]))
		return (ft_gbtabfree(cmd_split, gb),
			ft_fdprintf(2, MSH E_EXPORT"'%s'"NT_VAL_ID, cmd->cmd), 0);
	while (cmd_split[0][i])
	{
		if (!ft_isalnum(cmd_split[0][i]) && cmd_split[0][i] != '_')
		{
			ft_fdprintf(2, MSH E_EXPORT"'%s'"NT_VAL_ID, cmd->cmd);
			return (ft_gbtabfree(cmd_split, gb), 0);
		}
		i++;
	}
	return (ft_gbtabfree(cmd_split, gb), 1);
}

int	export_error_management(t_msh *msh, t_cmd_lst *cmd, int *error_code)
{
	if (ft_strncmp(cmd->cmd, "=", 1) == 0 || cmd->is_nill)
		return (*error_code = 1,
			ft_fdprintf(2, MSH E_EXPORT"'%s'"NT_VAL_ID, cmd->cmd), 0);
	if (ft_strncmp(cmd->cmd, "-", 1) == 0)
		return (*error_code = 2,
			ft_fdprintf(2, MSH E_EXPORT"'%s'"INVALID_OPT, cmd->cmd), 0);
	if (!verif_first_arg(&(msh->garbage), cmd))
		return (*error_code = 1, 0);
	return (1);
}
