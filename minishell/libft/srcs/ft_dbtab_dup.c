/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbtab_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:39:14 by nfaust            #+#    #+#             */
/*   Updated: 2023/05/26 15:52:12 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dbtab_dup(char **dbtab)
{
	size_t	i;
	char	**new_dbtab;

	if (!dbtab)
		return (NULL);
	i = 0;
	while (dbtab[i])
		i++;
	new_dbtab = malloc(sizeof(char *) * (i + 1));
	if (!new_dbtab)
		return (NULL);
	i = 0;
	while (dbtab[i])
	{
		new_dbtab[i] = ft_strdup(dbtab[i]);
		if (!new_dbtab)
			return (NULL);
		i++;
	}
	new_dbtab[i] = NULL;
	return (new_dbtab);
}
