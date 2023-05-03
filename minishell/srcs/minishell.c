/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/03 12:04:18 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char **envp)
{
	char	*line;
	char 	**arg;
	(void)envp;
	char	path[256];
	while (1)
	{
		line = readline("$ >> ");
		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		if (ft_strncmp(line, "pwd", 4) == 0)
		{
			getcwd(path, sizeof(path));
			printf("%s\n", path);
		}
		if (line && *line)
			add_history(line);
		arg = parsing_argu(line);
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
