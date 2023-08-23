/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:59:14 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/20 13:23:18 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
		{
			if (ft_strncmp(line + i, "=""", 3) == 0 || line[i + 1] == '\0')
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	b_env(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->envp[i])
	{
		if (is_empty(msh->envp[i]))
			printf("%s\n", msh->envp[i]);
		i++;
	}
	return (0);
}
