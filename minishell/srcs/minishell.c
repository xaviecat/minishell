/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/31 19:57:56 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_minish	*create_minishell(char **envp)
{
	t_minish		*sh;

	sh = malloc(sizeof(t_minish));
	if (!sh)
		return (NULL); // ! ERROR
	sh->envp = envp;
	sh->cmds = NULL;
	sh->lst_c = NULL;
	sh->lst_w = NULL;
	sh->garbage = NULL;
	sh->garbage = create_garbage_container();
	if (!sh->garbage)
	{
		free(sh);
		return (NULL);
	}
	return (sh);
}

void	minishell(char **envp)
{
	char		*line;
	t_minish	*minish;

	printf(LBLUE TRISHBANNER0"\n");
	printf(TRISHBANNER1"\n");
	printf(TRISHBANNER2"\n");
	printf(TRISHBANNER3"\n");
	printf(TRISHBANNER4"\n");
	printf(TRISHBANNER5"\n");
	printf(TRISHBANNER6"\n");
	printf(TRISHBANNER7"\n");
	printf(BOLD TRISHBANNER8"\n" RESET);
	while (1)
	{
		line = readline(GREEN UNDERLINE"TRI_SH $>"RESET" ");
		if (line && *line)
			add_history(line);
		minish = create_minishell(envp);
		if (!minish)
			return ; // ! ERROR
		if (!(create_char_lst_with_c_inside(line, &minish)))
		{
			free(line);
			free(minish->garbage);
			free(minish);
			return ;
		}
		give_type_in_lst(&minish->lst_c);
		print_lst_char(minish->lst_c);
		if (process_quotes(minish->lst_c) == true)
			ft_fdprintf(2, RED"ERROR : QUOTE DON'T CLOSED"RESET);// ! free
		if (is_forbidden_char(minish->lst_c))
			ft_fdprintf(2, RED"checked\n"RESET); // ! free
		if (is_bad_redir(minish->lst_c))
			ft_fdprintf(2, RED"ERRROR BAD REDIR\n"RESET); // ! free
		harmonize_spaces(minish->lst_c, &(minish->garbage));
		print_lst_char(minish->lst_c);
		if (!(create_word_lst(&minish)))
		{
			free(minish->garbage);
			free(minish);
			return ;
		}
		//! gerer quand metacractere en fin de ligne
		print_lst_word(minish->lst_w);
		expand_commands(&minish->lst_w, envp);
		print_lst_word(minish->lst_w);
		sh_pars(&minish); //! getsion sortie d'erreur
		print_lst_cmd(minish->cmds);
//		if (ft_strncmp(line, "exit", 5) == 0)
//			break ;
//		if (ft_strncmp(line, "pwd", 4) == 0)
//			pwd(envp);
//		arg = parsing_argu(line);
//		if (ft_strncmp(arg[0], "cd", 3) == 0)
//			cd(arg[1], envp);
//		(void) arg;
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
		ft_free_all(&minish->garbage);
		free(minish);
	}
	lst_clear(&minish->cmds);
	free(line);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
// 	(void) envp;
//	(void) argc;
	if (argc == 1)
		minishell(envp);
	return (1);
}
