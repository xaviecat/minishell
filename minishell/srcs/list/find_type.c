/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:17:00 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/16 15:03:46 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief give a type to the character c
 * @param c
 * @return type of character
 */
int	find_type_of_c(char c)
{
	if (c == 9 || c == 32)
		return (space);
	if (c == '\'')
		return (s_quote);
	if (c == '\"')
		return (d_quote);
	if (c == '|')
		return (c_pipe);
	if (c == '-')
		return (dash);
	if (c == '<' || c == '>')
		return (a_bracket);
	if (c == '$')
		return (dollar);
	return (charc);
}

/**
 * @brief find the type to all the list of character
 * @param lst
 */
void	give_type_in_lst(t_char_lst **lst)
{
	t_char_lst	*first;

	first = *lst;
	while (*lst)
	{
		(*lst)->type = find_type_of_c((*lst)->c);
		*lst = (*lst)->next;
	}
	*lst = first;
}

/**
 * @brief make sure that the command we got as not a character we don't want
 * @param command
 * @return 1 if command is good, 0 if is not
 */
int check_command_is_fine(char *command)
{
    int i;

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
}