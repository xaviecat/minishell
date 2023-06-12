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

void	b_exit(t_minish **minish)
{
	ft_free_all(&((*minish)->garbage));
	free((*minish)->garbage);
	(*minish)->garbage = NULL;
	free(*minish);
	minish = NULL;
	exit(EXIT_SUCCESS);
}
