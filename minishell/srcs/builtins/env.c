/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:59:14 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/08 15:24:44 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_empty(char *line)
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

void	b_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (is_empty(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
	return ;
}