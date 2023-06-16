/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:59:21 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/15 17:22:20 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
int	parsing_char(t_msh **minish, char *line, char **envp_sh)
{
	if (!(create_char_lst_with_c_inside(line, minish)))
	{
		free(line);
		free_and_exit_minish(*minish, &envp_sh);
	}
	give_type_in_lst(&(*minish)->lst_c);
	if (unhandled_char((*minish)->lst_c))
		return (ft_free_all(&(*minish)->garbage), 0);
	harmonize_spaces(&((*minish)->lst_c), &((*minish)->garbage));
//	print_lst_char((*minish)->lst_c);
	return (1);
}

int	parsing_word(t_msh **minish, char **envp_sh)
{
	if (!(create_word_lst(minish)))
		free_and_exit_minish(*minish, &envp_sh);
	if ((!check_pipe_and_redir(&((*minish)->garbage), &((*minish)->lst_w))))
		return (0);
	if (!expand_commands(*minish))
	{
		ft_free_all(&((*minish)->garbage)),
		free_and_exit_minish(*minish, &envp_sh);
	}
//	print_lst_word((*minish)->lst_w);
	return (1);
}

int	parsing_cmd(t_msh **minish, char **envp_sh)
{
	if (!(sh_pars(minish)))
		free_and_exit_minish(*minish, &envp_sh);
	if (!heredoc_handling(*minish))
	{
		ft_free_all(&((*minish)->garbage)),
		free_and_exit_minish(*minish, &envp_sh);
	}
	if (!ft_del_quotes(*minish))
	{
		ft_free_all(&((*minish)->garbage)),
		free_and_exit_minish(*minish, &envp_sh);
	}
	get_access(minish);
	print_lst_cmd((*minish)->lst_n);
	return (1);
}

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
