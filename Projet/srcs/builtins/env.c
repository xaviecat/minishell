/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:59:14 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/20 08:42:12 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Checking if variable has content
 * @param line
 * @return 0 if it has content, 1 if not
 */
static int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief display variable from envp if has content
 * @param msh
 * @return 0 to set the exit status to 0
 */
int	b_env(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->envp[i])
	{
		if (!is_empty(msh->envp[i]))
			printf("%s\n", msh->envp[i]);
		i++;
	}
	return (0);
}
