/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:10:58 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/19 14:27:57 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	export_error_management(t_msh *msh, t_cmd_lst *cmd)
{
	int	error_code;

//	error_code = quote_quote_handling(cmd);
	error_code = 1;
	if (error_code <= 0)
		return (error_code);
	(void) msh;
	(void) cmd;
	return (1);
}

//
//
//export $fhsjd banane=test
//
//export
//        $erfs=test
//		banane=test;
//export
//		"=test"
//		"banane=test";
//
//export =test banane="test  youpi";
//
//export =test banane =test NULL ;
