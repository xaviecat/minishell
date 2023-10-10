/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_str_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:54:37 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/07 12:04:59 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief checks whether a string array is lexicographically sorted
 * @return 1 if not sorted \n 0 else
 */
static int	not_sorted(char **str_arr)
{
	size_t	i;

	i = 0;
	while (str_arr[i] && str_arr[i + 1])
	{
		if (ft_strcmp(str_arr[i], str_arr[i + 1]) > 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief sorts a string array lexicographically
 */
void	ft_sort_str_arr(char **str_arr)
{
	size_t	i;
	char	*tmp;

	while (not_sorted(str_arr))
	{
		i = 0;
		while (str_arr[i] && str_arr[i + 1])
		{
			if (strcmp(str_arr[i], str_arr[i + 1]) > 0)
			{
				tmp = str_arr[i];
				str_arr[i] = str_arr[i + 1];
				str_arr[i + 1] = tmp;
			}
			i++;
		}
	}
}
