/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:53 by xcharra           #+#    #+#             */
/*   Updated: 2023/04/26 14:11:46 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

/* malloc, free, exit, getenv, tcsetattr, tcgetattr, */
# include <stdlib.h>

/* open */
# include <fcntl.h>

/* close, read, write, access, dup, dup2, execve, fork, pipe, unlink
, rl_*, getcwd, chdir, stat, lstat, fstat, isatty, ttyname,ttyslot */
# include <unistd.h>

/* perror printf readline ??*/
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>


/* strerror */
# include <string.h>

/* wait, waitpid, wait3, wait4 */
# include <sys/wait.h>

/* signal, sigaction, sigemptyset, siggadset, kill */
# include <signal.h>

/* opendir,readdir, closedir */
# include <dirent.h>

/* ioctl,  */
# include <sys/ioctl.h>

/* tgetent, tgetflag, tgetnum, tgetstrr, tgoto, tputs */
# include <curses.h>
# include <term.h>

/* errno */
# include <errno.h>

#endif
