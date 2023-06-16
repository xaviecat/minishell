/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/16 10:33:51 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int g_exit_status = 0;

t_msh	*create_minishell(char **envp, char **envp_sh)
{
	t_msh		*sh;

	sh = malloc(sizeof(t_msh));
	if (!sh)
		return (NULL);
	sh->lst_n = NULL;
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
		sh->envp = ft_gbtabdup(envp_sh, &(sh->garbage));
	else
		sh->envp = ft_gbtabdup(envp, &(sh->garbage));
	return (sh);
}

void	free_and_exit_minish(t_msh *minish, char ***envp_sh)
{
	if (*envp_sh)
		ft_gbtabfree(*envp_sh, &(minish->garbage));
	envp_sh = NULL;
	free(minish->garbage);
	free(minish);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	cp_envp_to_envp_sh(char ***envp_sh, char **envp_in_minish)
{
	if (*envp_sh)
		ft_tabfree(*envp_sh);
	*envp_sh = ft_tabdup(envp_in_minish);
}

void	minishell(char **envp)
{
	char		*line;
	t_msh		*msh;
	char		**envp_sh;

	envp_sh = NULL;
	print_bannier();
	signal_hub_term();
	while (1)
	{
		line = readline(GREEN UNDERLINE"TRI_SH $>"RESET" ");
		if (!line || *line == '\0')
		{
			if (line)
			{
				free(line);
				continue ;
			}
			else
			{
				printf("exit");
				break ;
			}
		}
		if (line && *line)
			add_history(line);
		msh = create_minishell(envp, envp_sh);
		if (!msh)
			return (free(line));
		if (!parsing_char(&msh, line, envp_sh))
			continue ;
		if (!parsing_word(&msh, envp_sh))
			continue ;
		parsing_cmd(&msh, envp_sh);
		if (!exec_all(msh))
		{
			ft_free_all(&(msh->garbage)),
			free_and_exit_minish(msh, &envp_sh);
		}
		execution(msh);
		cp_envp_to_envp_sh(&envp_sh, msh->envp);
		ft_free_all(&msh->garbage);
		free(msh);
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
