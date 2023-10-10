/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/10/10 13:19:33 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_exit_status = 0;

void	exit_msh_malloc_prob(char *line, char **envp_sh)
{
	if (envp_sh)
		ft_tabfree(envp_sh);
	return (free(line));
}

void	minishell(char **envp)
{
	char		*line;
	t_msh		*msh;
	char		**envp_sh;
	int			ret_line;

	msh = NULL;
	envp_sh = NULL;
	while (1)
	{
		signal_hub_term();
//		printf("%d ", g_exit_status);
		line = readline(GREEN UNDERLINE"TRI_SH $>"RESET" ");
		ret_line = line_empty_or_exit(line, envp_sh);
		if (ret_line == 1)
			continue ;
		if (ret_line == 2)
			break ;
		if (line && *line)
			add_history(line);
		msh = create_minishell(envp, envp_sh);
		if (!msh)
			return (exit_msh_malloc_prob(line, envp_sh));
		if (routine_minishell(msh, line, &envp_sh))
			continue ;
		free_end_loop(msh, &envp_sh);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	if (argc == 1)
		minishell(envp);
	return (g_exit_status);
}
