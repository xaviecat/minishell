/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:10:58 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/19 15:21:53 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	export_error_management(t_msh *msh, t_cmd_lst *cmd)
{
	int	error_code;

	(void)cmd;
	error_code = 1;
	if (error_code <= 0)
		return (error_code);
	(void) msh;
	return (1);
}
