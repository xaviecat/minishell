/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gb_dbtab_join.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:51:11 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/02 13:51:11 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

size_t	count_char_pt(char **tab1, char **tab2)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (tab1[i++])
		counter++;
	i = 0;
	while (tab2[i++])
		counter++;
	return (counter);
}

void	ft_free_joined_tab(char **dst_tab, t_garbage **gb)
{
	size_t	i;

	i = 0;
	while (dst_tab[i])
		ft_free(gb, dst_tab[i++]);
	ft_free(gb, dst_tab);
}

int	allocate_inside(char **dst_tab, char **tab1, char **tab2, t_garbage **gb)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (tab1[i])
	{
		dst_tab[j] = ft_malloc(gb, sizeof(char), ft_strlen(tab1[i++]));
		if (!dst_tab[j++])
			return (ft_free_joined_tab(dst_tab, gb), 0);
	}
	i = 0;
	while (tab2[i])
	{
		dst_tab[j] = ft_malloc(gb, sizeof(char), ft_strlen(tab2[i++]));
		if (!dst_tab[j++])
			return (ft_free_joined_tab(dst_tab, gb), 0);
	}
	return (0);
}

char	**ft_gb_dbtab_join(char **tab1, char **tab2, t_garbage **gb)
{
	size_t	char_pt_count;
	char	**joined_tab;

	if (!tab1 && !tab2)
		return (NULL);
	if (!tab1)
		return (tab2);
	if (!tab2)
		return (tab1);
	char_pt_count = count_char_pt(tab1, tab2);
	joined_tab = ft_malloc(gb, sizeof(char *), char_pt_count);
	if (!joined_tab)
		return (NULL);
	if (!allocate_inside(joined_tab, tab1, tab2, gb))
		return (NULL);
}
