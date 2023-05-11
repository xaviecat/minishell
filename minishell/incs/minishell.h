/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:53 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/11 17:51:42 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incs/libft.h"

/* malloc, free, exit, getenv, tcsetattr, tcgetattr, */
# include <stdlib.h>

/* open */
# include <fcntl.h>

/* close, read, write, access, dup, dup2, execve, fork, pipe, unlink
, rl_*, getcwd, chdir, stat, lstat, fstat, isatty, ttyname,ttyslot */
# include <unistd.h>

/* perror printf readline ??*/
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>


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

/* structure */
typedef struct s_cmd_list
{
	char				**cmd;
	bool				builtin;
	struct s_cmd_list	*next;
	struct s_cmd_list	*previous;
}				t_cmd_list;

typedef struct s_minish
{
	char		**envp;
	t_cmd_list	*cmds;
}				t_minish;

/* parsing */
char	**parsing_argu(char *arg_term);
t_minish	*parsing_command(char *cmd_line, t_minish *sh);
void	expand_commands(t_minish **minish);

/* builtins */
void	pwd(char **envp);
void	cd(char *path, char **envp);

/* utils */
char	*ft_strdup_to_x(char *str, char x);

/* list command */
t_cmd_list	*lst_cmd_new(char *content);
void	lst_cmd_add_back(t_cmd_list **lst, t_cmd_list *new);
void	print_list(t_cmd_list *lst);
void 	lst_clear(t_cmd_list **lst);
#endif
