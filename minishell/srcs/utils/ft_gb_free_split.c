/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gb_free_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:36:24 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/02 14:41:22 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_gb_free_split(char **tab_to_free, t_garbage **gb)
{
	size_t	i;

	i = 0;
	while (tab_to_free[i])
		ft_free(gb, tab_to_free[i++]);
	ft_free(gb, tab_to_free);
}
