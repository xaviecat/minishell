/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/01 18:08:21 by syluiset         ###   ########.fr       */
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

void	free_and_exit_minish(t_minish *minish)
{
	free(minish->garbage);
	free(minish);
	exit(EXIT_FAILURE);
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
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		if (line && *line)
			add_history(line);
		minish = create_minishell(envp);
		if (!minish)
			return ; // ! ERROR
		if (!(create_char_lst_with_c_inside(line, &minish)))
		{
			free(line);
			free_and_exit_minish(minish);
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
			free_and_exit_minish(minish);
		if ((!redir_is_valid(&(minish->lst_w), &(minish->garbage))))
			continue ;
		//! gerer redir in redir >< "bash: syntax error near unexpected token `<'"
		//! gerer quand chevron ou pipe en fin de ligne
		print_lst_word(minish->lst_w);
		expand_commands(minish);
		print_lst_word(minish->lst_w);
		if (!(sh_pars(&minish)))
			free_and_exit_minish(minish);
		print_lst_cmd(minish->cmds);
		exec_all(minish);
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
