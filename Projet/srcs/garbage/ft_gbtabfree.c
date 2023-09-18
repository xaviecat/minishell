/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:45:29 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/02 13:45:29 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_gbtabfree(char **tbl, t_garbage **gb)
{
	size_t	i;

	i = 0;
	if (!tbl)
		return ;
	while (tbl[i])
	{
		ft_free(gb, tbl[i]);
		i++;
	}
	ft_free(gb, tbl);
}
