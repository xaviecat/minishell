/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gbtabdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:24:46 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/02 14:01:15 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**ft_gbtabdup(char **dbtab, t_garbage **gb)
{
	int		i;
	char	**new_tab;

	if (!dbtab)
		return (NULL);
	i = 0;
	while (dbtab[i])
		i++;
	new_tab = ft_malloc(gb, sizeof(char *), (i + 1));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (dbtab[i])
	{
		new_tab[i] = ft_gbstrdup(dbtab[i], gb);
		if (!new_tab[i])
			return (ft_gbtabfree(new_tab, gb), NULL);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
