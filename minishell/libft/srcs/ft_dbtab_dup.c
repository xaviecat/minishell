/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbtab_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:39:14 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/02 14:01:15 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	**ft_dbtab_dup(char **dbtab)
{
	int		i;
	char	**new_dbtab;

	new_dbtab = NULL;
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
		if (!new_dbtab[i])
		{
			while (--i >= 0)
				free(new_dbtab[i]);
			free(new_dbtab);
			return (NULL);
		}
		i++;
	}
	new_dbtab[i] = NULL;
	return (new_dbtab);
}
