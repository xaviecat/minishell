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

/**
 * @brief Duplicate an array and include him in the garbage
 * @param tab The array to duplicate
 * @return The new duplicated array or NULL if there are an error
 */
char	**ft_gbtabdup(char **tab, t_garbage **gb)
{
	int		i;
	char	**new_tab;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
		i++;
	new_tab = ft_malloc(gb, sizeof(char *), (i + 1));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_gbstrdup(tab[i], gb);
		if (!new_tab[i])
			return (ft_gbtabfree(new_tab, gb), NULL);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
