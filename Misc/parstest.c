/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parstest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:12:35 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/10 12:12:35 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/libft/incs/libft.h"

int main(int argc, char *argv[], char *envp[])
{
	char	**parsedCmdLine;
	char	*cmdLine = {"cmd -art | cat -en > outfile"};
	int		i;

	(void) argc;
	(void) argv;
	(void) envp;
	parsedCmdLine = ft_split(cmdLine, ' ');
	i = 0;
	while (parsedCmdLine[i])
	{
		ft_printf("arg[%d] = %s\n", i, parsedCmdLine[i]);
		i++;
	}
	i = 0;
	ft_free_split(parsedCmdLine);
}
