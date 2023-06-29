/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:59:21 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/29 16:17:27 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
int	parsing_char(t_msh **msh, char *line)
{
	if (!(create_char_lst_with_c_inside(line, msh)))
	{
		g_exit_status = 128 + 12;
		free(line);
		free_and_exit_minish(*msh);
	}
	give_type_in_lst(&(*msh)->lst_c);
	if (unhandled_char((*msh)->lst_c))
	{
		g_exit_status = 2;
		return (free_end_loop(*msh), 0);
	}
	harmonize_spaces(&((*msh)->lst_c), &((*msh)->garbage));
	//print_lst_char((*msh)->lst_c);
	return (1);
}

int	parsing_word(t_msh **msh)
{
	int	ret;

	ret = create_word_lst(msh);
	if (ret == 1)
		free_and_exit_minish(*msh);
	else if (ret == 2)
		return (free_end_loop(*msh), 0);
	if ((!check_pipe_and_redir(&((*msh)->garbage), &((*msh)->lst_w))))
		return (free_end_loop(*msh), 0);
	ret = expand_commands(*msh);
	if (ret == 0)
		free_and_exit_minish(*msh);
	if (ret == 2)
		return (free_end_loop(*msh), 0);
	//print_lst_word((*msh)->lst_w);
	return (1);
}

int	parsing_cmd(t_msh **msh)
{
	int ret;

	if (!(sh_pars(msh)))
		free_and_exit_minish(*msh);
	ret = heredoc_handling(*msh);
	if (ret == 0)
		free_and_exit_minish(*msh);
	if (ret == 2)
		return (free_end_loop(*msh), 0);
	if (!ft_del_quotes(*msh))
		free_and_exit_minish(*msh);
	get_access(*msh);
	(*msh)->n_node = count_command((*msh)->lst_n);
//	printf("\nnombre commande:%zu\n", (*msh)->n_node);
//	print_lst_cmd((*msh)->lst_n);
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
