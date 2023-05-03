/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/03 12:55:11 by syluiset         ###   ########.fr       */
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
			if (!getcwd(path, sizeof(path)))
				printf("i dont know where i am\n");
			else
				printf("%s\n", path);
		}
		if (line && *line)
			add_history(line);
		arg = parsing_argu(line);
		if (ft_strncmp(arg[0], "cd", 3) == 0)
			chdir(arg[1]);
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
