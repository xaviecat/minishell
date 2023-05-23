/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/22 14:05:56 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_minish	*create_minishell(char **envp)
{
	t_minish	*sh;

	sh = malloc(sizeof(t_minish));
	sh->envp = envp;
	sh->cmds = NULL;
	return (sh);
}


void	minishell(char **envp)
{
	char		*line;
	//char		**arg;
	t_minish	*minish;
	t_char_lst	*lst_c;
	 t_word_lst	*lst_w;
	minish = create_minishell(envp);
	while (1)
	{
		line = readline("TRI_SH $> ");
		if (line && *line)
			add_history(line);
		lst_c = create_char_lst_with_c_inside(line);
		give_type_in_lst(&lst_c);
		if (process_quotes(lst_c) == true)
			ft_fdprintf(2, "ERROR : QUOTE DON'T CLOSED");// ! free
		printf("lst of char :\n");
		print_lst(lst_c);
		printf("\n");
		if (is_forbidden_char(lst_c))
			ft_fdprintf(2, "checked\n");
		lst_w = create_word_lst(lst_c);
		//printf("lst of word :");
		//print_lst_w(lst_w);
		//printf("\n");
		expand_commands(&lst_w, envp);
		sh_pars(&lst_w, &minish);
		printf("list of command :\n");
		print_list(minish->cmds);
//		if (ft_strncmp(line, "exit", 5) == 0)
//			break ;
//		if (ft_strncmp(line, "pwd", 4) == 0)
//			pwd(envp);
//		arg = parsing_argu(line);
//		if (ft_strncmp(arg[0], "cd", 3) == 0)
//			cd(arg[1], envp);
//		(void) arg;
		free(line);
	}
	lst_clear(&minish->cmds);
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
