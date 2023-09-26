/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:59:21 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/26 10:28:34 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief split all caractere in node
 * @param msh
 * @param line
 * @return 0 if failed, 1 if it work
 */
int parsing_char(t_msh **msh, char *line)
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
	if (harmonize_spaces(&((*msh)->lst_c), &((*msh)->garbage)))
		return (free_and_exit_minish(*msh), 0);
	return (1);
}

/**
 * @brief reforme word in word node
 * @param msh
 * @return 0 if fail, 1 if it work
 */
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
	return (1);
}

/**
 * @brief reforme command from word in node
 * @param msh
 * @return 0 if failed, 1 if it work
 */
int	parsing_cmd(t_msh **msh)
{
	int	ret;

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
	return (1);
}

/**
 * @brief pars content in an new msh struct
 * @param envp
 * @param envp_sh
 * @return
 */
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
	sh->n_node = 0;
	sh->garbage = create_garbage_container();
	if (!sh->garbage)
	{
		free(sh);
		return (NULL);
	}
	if (envp_sh)
	{
		sh->envp = ft_gbtabdup(envp_sh, &(sh->garbage));
		ft_tabfree(envp_sh);
		if (!sh->envp)
			return (free(sh->garbage), free(sh), NULL);
	}
	else
		sh->envp = ft_gbtabdup(envp, &(sh->garbage));
	return (sh);
}

int	line_empty_or_exit(char *line, char **envp_sh)
{
	if (!line || *line == '\0')
	{
		if (line)
		{
			free(line);
			return (1);
		}
		else
		{
			printf("exit\n");
			if (envp_sh)
				ft_tabfree(envp_sh);
			return (2);
		}
	}
	return (0);
}
