/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:43:08 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/23 10:07:39 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

bool	is_forbidden_char(t_char_lst *lst)
{
	while (lst)
	{
		if (lst->c == '&' && lst->next && lst->next->c == '&'
			&& !lst->s_quote && !lst->d_quote)
			return (ft_fdprintf(2, "minishell: syntax error near unexpected token '&&'\n"), true);
		if (lst->c == '|' && lst->next && lst->next->c == '|'
			&& !lst->s_quote && !lst->d_quote)
			return (ft_fdprintf(2, "minishell: syntax error near unexpected token '||'\n"), true);
		if (lst->c == ';' && !lst->s_quote && !lst->d_quote)
			return (ft_fdprintf(2, "minishell: syntax error near unexpected token ';'\n"), true);
		lst = lst->next;
	}
	return (false);
}

/**
 * @brief make sure that the command we got as not a character we don't want
 * @param command
 * @return 1 if command is good, 0 if is not
 *//*

int	check_command_is_fine(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '\\')
			return (0); // ! ERROR
		if (command[i] == ';')
			return (0); // ! ERROR
		if (ft_strncmp(command + i, "&&", 2) == 0)
			return (0); // ! ERROR
		if (ft_strncmp(command + i, "||", 2) == 0)
			return (0); // ! ERROR
		i++;
	}
	return (1);
}*/
