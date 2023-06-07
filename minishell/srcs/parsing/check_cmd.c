/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:08:59 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/07 15:12:06 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	check_command(t_w_cmd_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->cmd)
		{

		}
		lst = lst->next;
	}
}