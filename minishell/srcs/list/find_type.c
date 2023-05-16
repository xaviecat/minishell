/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:17:00 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/15 14:38:23 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"



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
		return (dollar);
	return (charc);
}

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

    i = 0;
    while (command[i])
    {
        if (command[i] == '\\')
            return (0); // ! ERROR
        if (command[i] == ';')
            return (0); // ! ERROR
        // if (command[i] == '\'')
        // {
        //     if (!(check_quote_are_close(command + i, '\'')))
        //         return (0); // ! ERROR
        // }
        // if (command[i] == '\"')
        // {
        //     if (!(check_quote_are_close(command + i, '\"')))
        //         return (0); // ! ERROR
        // }
        i++;
    }
    return (1);
}