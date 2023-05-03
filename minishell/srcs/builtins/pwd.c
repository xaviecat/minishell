/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:00:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/03 17:59:05 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* proteger getcwd */
void	pwd(void)
{
	char	path[256];

	if (!getcwd(path, sizeof(path)))
		printf("i dont know where i am\n");
	else
		printf("%s\n", path);
}
