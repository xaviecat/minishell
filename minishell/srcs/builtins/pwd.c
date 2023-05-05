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
//PWD DISPONIBLE DANS ENVP
void	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		printf("i dont know where i am\n");
	else
		printf("%s\n", path);
	free(path);
}
