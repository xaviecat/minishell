/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:39:14 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/14 13:44:43 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab)
{
	int		i;
	char	**newtab;

	newtab = NULL;
	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
		i++;
	newtab = malloc(sizeof(char *) * (i + 1));
	if (!newtab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		newtab[i] = ft_strdup(tab[i]);
		if (!newtab[i])
		{
			ft_tabfree(newtab);
			return (NULL);
		}
		i++;
	}
	newtab[i] = NULL;
	return (newtab);
}
