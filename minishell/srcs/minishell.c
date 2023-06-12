/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/08 12:26:10 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_minish	*create_minishell(char **envp, char **envp_sh)
{
	t_minish		*sh;

	sh = malloc(sizeof(t_minish));
	if (!sh)
		return (NULL); // ! ERROR
	sh->cmds = NULL;
	sh->lst_c = NULL;
	sh->lst_w = NULL;
	sh->garbage = NULL;
	sh->garbage = create_garbage_container();
	(void)envp;
	(void)envp_sh;
	if (!sh->garbage)
	{
		free(sh);
		return (NULL);
	}
	if (envp_sh)
		sh->envp = ft_dbtab_dup_gb(envp_sh, &(sh->garbage));
	else
		sh->envp = ft_dbtab_dup_gb(envp, &(sh->garbage));
	return (sh);
}

void	free_and_exit_minish(t_minish *minish, char ***envp_sh)
{
	if (*envp_sh)
		free_char_tab_gb(*envp_sh, &(minish->garbage));
	envp_sh = NULL;
	free(minish->garbage);
	free(minish);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	cp_envp_to_envp_sh(char ***envp_sh, char **envp_in_minish)
{
	if (*envp_sh)
		free_char_tab(*envp_sh);
	*envp_sh = ft_dbtab_dup(envp_in_minish);
}

void	minishell(char **envp)
{
	char		*line;
	t_minish	*minish;
	char		**envp_sh;

	/* TEST SIGNAL */
	struct	sigaction	sa_int;
	struct	sigaction	sa_quit;
	struct	sigaction	sa_stop;
	//Ctrl+C
	sa_int.sa_handler = signal_handler;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	//(Ctrl+\)
	sa_quit.sa_handler = signal_handler;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	//Ctrl+D
	sa_stop.sa_handler = signal_handler;
	sa_stop.sa_flags = 0;
	sigaction(SIGTSTP, &sa_stop, NULL);
	/* TEST SIGNAL */

	envp_sh = NULL;
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
			continue ;
		}
		if (line && *line)
			add_history(line);
		minish = create_minishell(envp, envp_sh);
		if (!minish)
			return ; // ! ERROR free line
		if (!(create_char_lst_with_c_inside(line, &minish)))
		{
			free(line);
			free_and_exit_minish(minish, &envp_sh);
		}
		give_type_in_lst(&minish->lst_c);
		if (unhandled_char(minish->lst_c))
		{
			ft_free_all(&minish->garbage);
			continue ;
		}
		harmonize_spaces(&(minish->lst_c), &(minish->garbage));
		print_lst_char(minish->lst_c);
		if (!(create_word_lst(&minish)))
			free_and_exit_minish(minish, &envp_sh);
		if ((!check_pipe_and_redir(&(minish->garbage), &(minish->lst_w))))
			continue ;
		//! gerer quand chevron avec epace
		if (!expand_commands(minish))
			return (ft_free_all(&(minish->garbage)),
				free_and_exit_minish(minish, &envp_sh), (void) 0);
		print_lst_word(minish->lst_w);
		if (!(sh_pars(&minish)))
			free_and_exit_minish(minish, &envp_sh);
		print_lst_cmd(minish->cmds);
		exec_all(minish);
		cp_envp_to_envp_sh(&envp_sh, minish->envp);
		ft_free_all(&minish->garbage);
		free(minish);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
//	(void) envp;
//	(void) argc;
	if (argc == 1)
		minishell(envp);
	return (1);
}
