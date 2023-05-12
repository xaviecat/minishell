/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/12 18:52:01 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_minish	*create_minishell(char **envp)
{
	t_minish	*sh;

	sh = malloc(sizeof(t_minish));
	sh->envp = envp;
	return (sh);
}

void	minishell(char **envp)
{
	char		*line;
	//char		**arg;
	t_minish	*minish;

	minish = create_minishell(envp);
	while (1)
	{
		line = readline("TRI_SH $>");
		minish = parsing_command(line, minish);
//		line = cut_whitespaces(ft_strdup(line));
//		printf("%s\n", line);
//		if (line)
//			free(line);
//		expand_commands(NULL, envp);
//		if (ft_strncmp(line, "exit", 5) == 0)
//			break ;
//		if (ft_strncmp(line, "pwd", 4) == 0)
//			pwd(envp);
//		if (line && *line)
//			add_history(line);
//		arg = parsing_argu(line);
//		if (ft_strncmp(arg[0], "cd", 3) == 0)
//			cd(arg[1], envp);
//		(void) arg;
		free(line);
	}
	lst_clear(&(minish->cmds));
	free(line);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	if (argc == 1)
		minishell(envp);
	return (1);
}
