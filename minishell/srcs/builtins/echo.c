/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:08:46 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/31 19:56:51 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

bool	param_n(t_w_cmd_list **lst)
{
	t_w_cmd_list	*first;
	int				i;
	bool			ret;

	ret = false;
	first = *lst;
	while (*lst)
	{
		if ((*lst)->cmd[0] != '-')
			return (ret);
		i = 1;
		while ((*lst)->cmd[i] && (*lst)->cmd[i] == 'n')
		{
			ret = true;
			i++;
			if ((*lst)->cmd[i] != '\0' && (*lst)->cmd[i] != 'n')
			{
				*lst = first;
				return (false);
			}
		}
		*lst = (*lst)->next;
	}
	return (ret);
}

void	b_echo(t_w_cmd_list *content)
{
	bool	new_line;

	if (!content)
		return ;
	content = content->next;
	new_line = param_n(&content);
	while (content)
	{
		printf("%s ", content->cmd);
		content = content->next;
	}
	if (!new_line)
		printf("\n");
}
