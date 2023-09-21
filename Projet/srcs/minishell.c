/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/09/21 16:42:48 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_exit_status = 0;

void	minishell(char **envp)
{
	char		*line;
	t_msh		*msh;
	char		**envp_sh;
	int			ret_line;

	envp_sh = NULL;
	while (1)
	{
		signal_hub_term();
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
			return (free(line));
		if (routine_minishell(msh, line, envp_sh))
			continue ;
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
