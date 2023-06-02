/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gb_dbtab_join.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:51:11 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/02 14:36:05 by nfaust           ###   ########.fr       */
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
			return (ft_gb_free_split(dst_tab, gb), 0);
	}
	i = 0;
	while (tab2[i])
	{
		dst_tab[j] = ft_malloc(gb, sizeof(char), ft_strlen(tab2[i++]));
		if (!dst_tab[j++])
			return (ft_gb_free_split(dst_tab, gb), 0);
	}
	return (0);
}

void	fill_tab(char **dst, char **tab1, char **tab2)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (tab1[j])
	{
		k = 0;
		while (tab1[j][k++])
			dst[i][k - 1] = tab1[j][k - 1];
		dst[i++][k - 1] = 0;
		j++;
	}
	j = 0;
	while (tab2[j])
	{
		k = 0;
		while (tab2[j][k++])
			dst[i][k - 1] = tab2[j][k - 1];
		dst[i++][k - 1] = 0;
		j++;
	}
	dst[i] = NULL;
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
	joined_tab = ft_malloc(gb, sizeof(char *), char_pt_count + 1);
	if (!joined_tab)
		return (NULL);
	if (!allocate_inside(joined_tab, tab1, tab2, gb))
		return (NULL);
	fill_tab(joined_tab, tab1, tab2);
	return (joined_tab);
}
