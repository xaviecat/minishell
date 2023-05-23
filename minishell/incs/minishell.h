/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:53 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/23 10:05:12 by syluiset         ###   ########.fr       */
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
	s_quote,
	d_quote,
	charc,
	c_pipe,
	dash,
	a_bracket,
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
	outfile,
	in_d_quote,
	in_s_quote
}			t_type_word;

typedef enum e_type_redir
{
	in,
	inin,
	out,
	outout
}			t_type_redir;

	/* list chaine*/

typedef struct s_redir_list
{
	t_type_redir		redir;
	char 				*filename;
	struct s_redir_list	*next;
}				t_redir_list;

typedef struct s_fd_list
{
	int 				in;
	int 				out;
	struct s_fd_list	*next;
}				t_fd_list;

typedef struct s_w_cmd_list
{
    char    *cmd;
    bool    s_quote;
    bool    d_quote;
    struct  s_w_cmd_list *next;
}               t_w_cmd_list;

typedef struct s_cmd_list
{
	t_w_cmd_list     	*cmd;
	bool				builtin;
	struct s_redir_list	*redirs;
	struct s_fd_list	*fds;
	struct s_cmd_list	*next;
	struct s_cmd_list	*previous;
}				t_cmd_list;

typedef struct s_word_lst
{
	char                *word;
	t_type_word			type;
	struct s_word_lst	*next;
	struct s_word_lst	*prev;
}						t_word_lst;

/**
 * @brief Contain the whole command line characters in chained list
 */
typedef struct s_char_lst
{
	int					pipe;
	char				c;
	t_type_char			type;
	bool				s_quote;
	bool				d_quote;
	bool				a_quote;
	struct s_char_lst	*prev;
	struct s_char_lst	*next;
}				t_char_lst;

typedef struct s_minish
{
	char		**envp;
	t_cmd_list	*cmds;
}				t_minish;

/* parsing */
char		**parsing_argu(char *arg_term);
t_minish	*parsing_command(char *cmd_line, t_minish *sh);
void		expand_commands(t_word_lst **w_lst, char **envp);
char		*cut_whitespaces(char *str);
bool		process_quotes(t_char_lst *lst);
t_redir_list	*get_redir(t_word_lst **lst);
void            print_redir(t_redir_list *lst);
t_fd_list	*create_fds_list(t_redir_list *redirs);
void    print_fd(t_fd_list *lst);

/* error */
bool		is_forbidden_char(t_char_lst *lst);


/* builtins */
void		pwd(char **envp);
void		cd(char *path, char **envp);

/* utils */
char		*ft_strdup_to_charset(char *str, char *charset);
int			ft_isspace(char c);
char		*str_cpy_to_x(char *src, char *dst, char x);
int			is_dollar_alone(char *env_var, char *cmd, size_t start);

/* list_char function */
t_char_lst	*char_lst_new(char c);
t_char_lst	*char_lst_last(t_char_lst *lst);
void		char_lst_add_back(t_char_lst **lst, t_char_lst *new);
void		char_lst_add_front(t_char_lst **lst, t_char_lst *new);
t_char_lst	*create_char_lst_with_c_inside(char *cmd_line);
void		give_type_in_lst(t_char_lst **lst);
void		print_lst(t_char_lst *lst);
void		char_lst_delone(t_char_lst **lst);

/* lst_word function */
t_word_lst	*create_word_lst(t_char_lst *old_lst);
void		print_lst_w(t_word_lst *lst);
char		*reforme_word(t_char_lst **lst_c);
int			is_a_bultin(char *word);
int			get_cat_of_word(char *word);
void		word_lst_delone(t_word_lst **lst);
t_word_lst	*word_lst_first(t_word_lst *lst);

/* list command maybe not useful */
t_cmd_list	*lst_cmd_new(t_w_cmd_list *cmds, t_fd_list *fds, t_redir_list *redir);
void		lst_cmd_add_back(t_cmd_list **lst, t_cmd_list *new);
void		print_list(t_cmd_list *lst);
void		lst_clear(t_cmd_list **lst);
t_cmd_list	*create_lst_cmd(t_word_lst **old_lst, t_fd_list *fds, t_redir_list *redirs);
void		sh_pars(t_word_lst **old_lst, t_minish **minish);
bool		builtin_or_command(char *cmd);
char		**get_cmd(t_word_lst **old_lst);

/* lst_w_cmd function */
t_w_cmd_list    *get_cmd_2(t_word_lst **old_lst);
#endif
