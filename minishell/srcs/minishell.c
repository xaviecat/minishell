/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/28 12:24:12 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int g_exit_status = 0;

void	free_and_exit_minish(t_msh *minish)
{
	//if (*envp_sh)
		//ft_gbtabfree(*envp_sh, &(minish->garbage));
	//envp_sh = NULL;
	ft_free_all(&(minish->garbage));
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

char	**cp_envp_to_envp_sh(char **envp_sh, char **envp_in_minish)
{
	envp_sh = ft_tabdup(envp_in_minish);
	return (envp_sh);
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
		signal_hub_term();
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
		if (!parsing_char(&msh, line))
			continue ;
		if (!parsing_word(&msh))
			continue ;
		parsing_cmd(&msh);
		if (!get_cmdtab(msh))
			free_and_exit_minish(msh);
		execution(msh);
		envp_sh = cp_envp_to_envp_sh(envp_sh, msh->envp);
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
