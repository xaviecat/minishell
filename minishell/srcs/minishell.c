/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/16 11:00:47 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int g_exit_status = 0;

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

void	free_end_loop(t_msh *msh)
{
	ft_free_all(&msh->garbage);
	free(msh->garbage);
	free(msh);
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
//	print_bannier();
	while (1)
	{
		line = readline(GREEN UNDERLINE"TRI_SH $>"RESET" ");
		signal_hub_term();
		if (!line || *line == '\0')
		{
			if (line)
			{
				free(line);
				continue ;
			}
			else
			{
				printf("exit\n");
				if (envp_sh)
					ft_tabfree(envp_sh);
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
		if (!get_cmdtab(msh))
		{
			ft_free_all(&(msh->garbage)),
			free_and_exit_minish(msh, &envp_sh);
		}
		execution(msh);
		cp_envp_to_envp_sh(&envp_sh, msh->envp);
		free_end_loop(msh);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	if (argc == 1)
		minishell(envp);
	return (1);
}
