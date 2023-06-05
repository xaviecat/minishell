/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_char_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:45:29 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/02 13:45:29 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_char_tab_gb(char **c_tab, t_garbage **gb)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_free(gb, c_tab[i]);
		i++;
	}
	ft_free(gb, c_tab);
}

void	free_char_tab(char **c_tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(c_tab[i]);
		i++;
	}
	free(c_tab);
}