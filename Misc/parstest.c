/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parstest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:12:35 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/10 17:49:57 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/libft/incs/libft.h"

int main(int argc, char *argv[], char *envp[])
{
	char	**parsedCmdLine;
	char	*cmdLine = {"cat << EOF | cat -en | grep \"salut\" >> outfile"};
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
	ft_free_split(parsedCmdLine);
}
/*
 * &camarche $camarchepas $? $$ > $
Split |
Rechercher les $
Redir : split << >> < > et open mot suivant puis del (detecter redir pour
 les fds)
Split ' '
Remove les quotes "l"''"s" > ls ou "l'"s' > l's
 dans le sens gauche vers droite

___
cat -en << EOF | cat -en | grep "salut" >> $USER
___
cat -en << EOF
 cat -en
 grep "salut" >> $USER
___
cat -en << EOF
 cat -en
 grep "salut" >> xcharra
___
cat -en
 cat -en
 grep "salut"
 ___
cat
-en

cat
-en

grep
"salut"
___
cat
-en

cat
-en

grep
salut
___
*/