/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:53 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/15 16:44:03 by syluiset         ###   ########.fr       */
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

	/* enum */

typedef enum e_type_char
{
	space,
	quote, // '
	d_quote, // "
	charc, // letter ect
	c_pipe, // |
	dash, // -
	a_bracket, // <
	dollar
}			t_type_char;

typedef enum e_type_word
{
	not_define,
	command,
	builtin,
	param,
	redir,
	hd,
	appnd,
	w_pipe,
	expand,
	open_file,
	delimiteur,
	infile,
	outfile
}			t_type_word;

	/* list chaine*/
typedef struct s_cmd_list
{
	char				**cmd;
	int					outfile;
	int					infile;
	bool				builtin;
	struct s_cmd_list	*next;
	struct s_cmd_list	*previous;
}				t_cmd_list;

typedef struct s_word_lst
{
	char                *word;
	t_type_word			type;
	struct s_word_lst    *next;
	struct s_word_lst    *prev;
}        t_word_lst;

typedef struct s_char_lst
{
	int					pipe;
	char				c;
	t_type_char			type;
	bool				quote;
	bool				d_quote;
	struct s_char_lst	*prev;
	struct s_char_lst	*next;
}				t_char_lst;

typedef struct s_minish
{
	char		**envp;
	t_cmd_list	*cmds;
}				t_minish;

/* checking*/
int		check_command_is_fine(char *command);

/* parsing */
char		**parsing_argu(char *arg_term);
t_minish	*parsing_command(char *cmd_line, t_minish *sh);
void		expand_commands(t_minish **minish);

/* builtins */
void		pwd(char **envp);
void		cd(char *path, char **envp);

/* utils */
char	*ft_strdup_to_x(char *str, char x);
int		iswhitespace(int c);

/* list_char function */
t_char_lst	*char_lst_new(char c);
t_char_lst	*char_lst_last(t_char_lst *lst);
void	char_lst_add_back(t_char_lst **lst, t_char_lst *new);
void	char_lst_add_front(t_char_lst **lst, t_char_lst *new);
t_char_lst	*create_char_lst_with_c_inside(char *cmd_line);
void	give_type_in_lst(t_char_lst **lst);
void	print_lst(t_char_lst *lst);
void	char_lst_delone(t_char_lst **lst);

/* lst_word function */
t_word_lst	*create_word_lst(t_char_lst *old_lst);
void		print_lst_w(t_word_lst *lst);
char		*reforme_word(t_char_lst **lst_c);

/* list command maybe not useful */
t_cmd_list	*lst_cmd_new(char *content);
void		lst_cmd_add_back(t_cmd_list **lst, t_cmd_list *new);
void		print_list(t_cmd_list *lst);
void		lst_clear(t_cmd_list **lst);
#endif
