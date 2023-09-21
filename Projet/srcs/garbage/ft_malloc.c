/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:57:31 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/12 17:07:31 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	*ft_malloc(t_garbage **garbage, int the_size, int number)
{
	t_garbage_lst	*new;
	void			*content;

	new = NULL;
	content = NULL;
	content = malloc(the_size * number);
	if (!content)
		return (NULL);
	new = new_garbage(content);
	if (!new)
		return (NULL);
	if (!(*garbage)->first)
	{
		(*garbage)->first = new;
		(*garbage)->last = new;
	}
	else
	{
		new->prev = (*garbage)->last;
		(*garbage)->last->next = new;
		(*garbage)->last = new;
	}
	return (content);
}
