/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gbcalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:42:51 by nfaust            #+#    #+#             */
/*   Updated: 2023/05/31 21:43:31 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	*ft_gbcalloc(size_t count, size_t size, t_garbage **gb)
{
	void	*mem;

	if (size && count >= 4294967295 / size)
		return (0);
	mem = ft_malloc(gb, size, count);
	if (!mem)
		return (NULL);
	ft_bzero(mem, count * size);
	return (mem);
}