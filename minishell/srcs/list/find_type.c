/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:17:00 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/12 17:58:43 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	iswhitespace(int c)
{
	if (c == 20 || c == 9 || c == 10)
		return (1);
	else
		return (0)
}

int	find_type_of_c(char c)
{
	if (iswhitespace(c))
		return (space);
	if (c == '\'')
		return (quote);
	if (c == '\"')
		return (d_quote);
	if (c == '|')
		return (c_pipe);
	if (c == '-')
		return (dash);
	if (c == '<' || c == '>')
		return (a_bracket);
	if (c == '$')
		return (charc);
}

int check_quote_are_close(char *command, char quote)
{
    int i;

    i = 0;
    while (command[i] != quote)
        i++;
    if (command[i])
        return (1);
    return (0);
}
int check_command_is_fine(char *command)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (command[i])
    {
        if (command[i] == '\\')
            return (0); // ! ERROR
        if (command[i] == ';')
            return (0); // ! ERROR
        if (command[i] == '\'')
        {
            if (!(check_quote_are_close(command + i, '\'')))
                return (0); // ! ERROR
        }
        if (command[i] == '\"')
        {
            if (!(check_quote_are_close(command + i, '\"')))
                return (0); // ! ERROR
        }
        i++;
    }
    return (1);
}