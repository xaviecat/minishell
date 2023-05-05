/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/03 17:56:21 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char **envp)
{
	char	*line;
	char	**arg;
	(void)envp;

	while (1)
	{
		line = readline("$ >> ");
		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		if (ft_strncmp(line, "pwd", 4) == 0)
			pwd();
		if (line && *line)
			add_history(line);
		arg = parsing_argu(line);
		if (ft_strncmp(arg[0], "cd", 3) == 0)
			cd(arg[1], envp);
		(void)arg;
		free(line);
	}
	free(line);
	rl_clear_history();
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
		minishell(envp);
	return (1);
}
