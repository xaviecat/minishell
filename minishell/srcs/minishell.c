/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/24 11:47:10 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_minish	*create_minishell(char **envp)
{
	t_minish		*sh;
    t_garbage_list  *gb;

    gb = malloc(sizeof(t_garbage_list));
    gb->content = NULL;
    gb->last_added = NULL;
    gb->next = NULL;
	sh = ft_malloc(&gb, sizeof(t_minish), 1);
	if (!sh)
    {
        free(gb);
		exit(EXIT_FAILURE); // ! ERROR
    }
	sh->envp = envp;
	sh->cmds = NULL;
	sh->lst_c = NULL;
	sh->lst_w = NULL;
	sh->garbage = gb;
	return (sh);
}

void	minishell(char **envp)
{
	char		*line;
	t_minish	*minish;

	while (1)
	{
	    minish = create_minishell(envp);
		line = readline("TRI_SH $> ");
		if (line && *line)
			add_history(line);
		create_char_lst_with_c_inside(line, &minish);
		give_type_in_lst(&minish->lst_c);
		if (process_quotes(minish->lst_c) == true)
			ft_fdprintf(2, "ERROR : QUOTE DON'T CLOSED");// ! free
		print_lst_char(minish->lst_c);
		printf("\n");
		if (is_forbidden_char(minish->lst_c))
			ft_fdprintf(2, "checked\n"); // ! free
		create_word_lst(&minish);
		print_lst_word(minish->lst_w);
		expand_commands(&minish->lst_w, envp);
		print_lst_word(minish->lst_w);
		sh_pars(&minish);
		printf("list of command :\n");
//		if (ft_strncmp(line, "exit", 5) == 0)
//			break ;
//		if (ft_strncmp(line, "pwd", 4) == 0)
//			pwd(envp);
//		arg = parsing_argu(line);
//		if (ft_strncmp(arg[0], "cd", 3) == 0)
//			cd(arg[1], envp);
//		(void) arg;
		print_lst_cmd(minish->cmds);
		// minish = parsing_command(line, minish);
		// if (ft_strncmp(line, "exit", 5) == 0)
		// 	break ;
		// if (ft_strncmp(line, "pwd", 4) == 0)
		// 	pwd(envp);
		// if (line && *line)
		// 	add_history(line);
		// arg = parsing_argu(line);
		// if (ft_strncmp(arg[0], "cd", 3) == 0)
		// 	cd(arg[1], envp);
		// (void) arg;
	//	b_echo(minish->cmds->cmd);
		ft_free_all(minish->garbage);
		free(minish);
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
