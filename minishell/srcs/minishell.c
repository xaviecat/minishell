/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/17 09:53:16 by syluiset         ###   ########.fr       */
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
	t_char_lst	*lst_c;
	t_word_lst	*lst_w;
	minish = create_minishell(envp);
	while (1)
	{
		line = readline("TRI_SH $> ");
        if (!(check_command_is_fine(line)))
            printf("ERROR\n");
        else
        {
            lst_c= create_char_lst_with_c_inside(line);
			give_type_in_lst(&lst_c);
			process_quotes(lst_c);
			print_lst(lst_c);
			lst_w = create_word_lst(lst_c);
			print_lst_w(lst_w);
			expand_commands(&lst_w, envp);
			print_lst_w(lst_w);
			printf("\n");
            create_lst_cmd(&lst_w);
        }
		//minish = parsing_command(line, minish);
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
