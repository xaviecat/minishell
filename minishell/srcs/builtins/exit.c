/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:05:10 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/12 11:29:36 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	b_exit(t_msh **msh)
{
	ft_free_all(&((*msh)->garbage));
	free((*msh)->garbage);
	(*msh)->garbage = NULL;
	free(*msh);
	msh = NULL;
	exit(EXIT_SUCCESS);
}
