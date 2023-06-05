/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbtab_dup_gb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:24:46 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/02 14:01:15 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**ft_dbtab_dup_gb(char **dbtab, t_garbage **gb)
{
    int	i;
    char	**new_dbtab;

    if (!dbtab)
        return (NULL);
    i = 0;
    while (dbtab[i])
        i++;
    new_dbtab = ft_malloc(gb, sizeof(char *), (i + 1));
    if (!new_dbtab)
        return (NULL);
    i = 0;
    while (dbtab[i])
    {
        new_dbtab[i] = ft_gb_strdup(dbtab[i], gb);
        if (!new_dbtab[i])
        {
            while (--i >= 0)
                ft_free(gb, new_dbtab[i]);
            ft_free(gb, new_dbtab);
            return (NULL);
        }
        i++;
    }
    new_dbtab[i] = NULL;
    return (new_dbtab);
}