/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:39:53 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/05 16:14:07 by syluiset         ###   ########.fr       */
/*   Updated: 2023/06/05 13:50:24 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//int	num_exit_status;

# include "../libft/incs/libft.h"
# include "colors.h"
# include "error_msgs.h"

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

typedef enum e_position
{
	prev,
	next,
}	t_position;

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

typedef struct s_garbage_list
{
	void					*content;
	struct s_garbage_list	*next;
	struct s_garbage_list	*prev;
}				t_garbage_list;

typedef struct s_garbage
{
	t_garbage_list	*first;
	t_garbage_list	*last;
}				t_garbage;

typedef struct s_redir_list
{
	t_type_redir		redir;
	char				*filename;
	struct s_redir_list	*next;
	struct s_redir_list	*last_added;
}				t_redir_list;

typedef struct s_fd_list
{
	int					in;
	int					out;
	struct s_fd_list	*next;
	struct s_fd_list	*last_added;
}				t_fd_list;

typedef struct s_w_cmd_list
{
	char				*cmd;
	bool				s_quote;
	bool				d_quote;
	struct s_w_cmd_list	*next;
	struct s_w_cmd_list	*last_added;
}				t_w_cmd_list;

typedef struct s_cmd_list
{
	t_w_cmd_list		*cmd;
	bool				builtin;
	struct s_redir_list	*redirs;
	struct s_fd_list	*fds;
	struct s_cmd_list	*next;
	struct s_cmd_list	*previous;
	struct s_cmd_list	*last_added;
}				t_cmd_list;

typedef struct s_word_lst
{
	char				*word;
	t_type_word			type;
	struct s_word_lst	*next;
	struct s_word_lst	*prev;
	struct s_word_lst	*last_added;
}						t_word_lst;

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
	struct s_char_lst	*last_added;
}				t_char_lst;

typedef struct s_minish
{
	char		**envp;
	t_cmd_list	*cmds;
	t_char_lst	*lst_c;
	t_word_lst	*lst_w;
	t_garbage	*garbage;
}				t_minish;

typedef bool	(*t_unhandled_char)(t_char_lst *);

/* parsing */
char			**parsing_argu(char *arg_term);
t_minish		*parsing_command(char *cmd_line, t_minish *sh);
int				expand_commands(t_minish *minish);
char			*cut_whitespaces(char *str, t_garbage **gb);
bool			process_quotes(t_char_lst *lst);
t_redir_list	*get_redir(t_word_lst **lst, t_garbage **gb);
void			print_redir(t_redir_list *lst);
t_fd_list		*create_fds_list(t_redir_list *redirs, t_garbage **gb);
void			print_fd(t_fd_list *lst);
void			harmonize_spaces(t_char_lst **lst, t_garbage **gb);
int				redir_is_valid(t_word_lst **lst, t_garbage **gb);
int				check_pipe_and_redir(t_garbage **gb, t_word_lst **lst);
int				ft_del_quotes(t_minish *msh);

/* error */
bool			is_forbidden_char(t_char_lst *lst);
bool			unhandled_char(t_char_lst *lst);
bool			is_bad_redir(t_char_lst *lst);
void			free_error_fds(t_garbage **gb, t_fd_list **lst);
void			free_error_redir(t_garbage **gb, t_redir_list **lst);
void			free_error_word_lst(t_garbage **gb, t_word_lst **lst);

/* builtins */
void			b_pwd(char **envp);
void			b_cd(char *path, char **envp);
void			b_echo(t_w_cmd_list *content);
void			b_exit(t_minish **minish);
int				b_export(t_minish *msh, t_w_cmd_list *cmds);
void			b_env(char **env);
void			find_builtin(t_minish *sh);

/* exec */
void			exec_all(t_minish *minish);

/* signal */
void			signal_handler(int signum);

/* utils */
char			*ft_cut_var(char *str, t_garbage **gb);
int				ft_isspace(char c);
char			*str_cpy_to_x(char *src, char *dst, char x);
int				is_dollar_alone(char *env_var, char *cmd, size_t start);
void			*ft_malloc(t_garbage **garbage, int the_size, int number);
void			ft_free_all(t_garbage **lst);
void			ft_free(t_garbage **lst, void *content);
t_garbage_list	*new_garbage(void *content);
t_garbage		*create_garbage_container(void);
void			garbage_add_back(t_garbage_list **lst, t_garbage_list *new);
char			*ft_gb_strdup(const char *src, t_garbage **gb);
void			get_first_garbage(t_garbage **lst);
char			*ft_gbstrjoin(char const *s1, char const *s2, t_garbage **gb);
void			ft_free_mcmd(char *env_var, char *cmd,
					char *exp_env_var, t_garbage **gb);
char			*fill_mdcmd(char *cmd, size_t start,
					char *exp_env_v, char *env_var);
void			*ft_gbcalloc(size_t count, size_t size, t_garbage **gb);
char			*ft_gbstrtrim(char const *s1, char const *set, t_garbage **gb);
char			**ft_dbtab_dup_gb(char **dbtab, t_garbage **gb);
void			free_char_tab(char **c_tab);
void			free_char_tab_gb(char **c_tab, t_garbage **gb);
char			**ft_gb_dbtab_join(char **tab1, char **tab2, t_garbage **gb);
void			ft_gb_free_split(char **tab_to_free, t_garbage **gb);
int				not_in_env(char *cmd, char **envp);
int				modify_envp(char *cmd, char **envp, t_garbage **gb);
void			ft_sort_str_arr(char **str_arr);
int				is_concat(char *cmd);



/* list_char function */
t_char_lst		*char_lst_new(char c, t_garbage **gb);
t_char_lst		*char_lst_last(t_char_lst *lst);
void			char_lst_add_back(t_char_lst **lst, t_char_lst *new);
void			char_lst_add_front(t_char_lst **lst, t_char_lst *new);
int				create_char_lst_with_c_inside(char *cmd_line, t_minish **sh);
void			give_type_in_lst(t_char_lst **lst);
void			print_lst_char(t_char_lst *lst);
void			char_lst_delone(t_char_lst **lst, t_garbage **gb);

/* lst_word function */
int				create_word_lst(t_minish **sh);
void			print_lst_word(t_word_lst *lst);
t_type_word is_a_bultin(char *word);
t_type_word get_cat_of_word(char *word);
void			word_lst_delone(t_word_lst **lst, t_garbage **gb);
t_word_lst		*word_lst_first(t_word_lst *lst);

/* list command maybe not useful */
t_cmd_list		*lst_cmd_new(t_w_cmd_list *cmds,
					t_fd_list *fds, t_redir_list *redir, t_garbage **gb);
void			lst_cmd_add_back(t_cmd_list **lst, t_cmd_list *new);
void			print_lst_cmd(t_cmd_list *lst);
void			lst_clear(t_cmd_list **lst);
t_cmd_list		*create_lst_cmd(t_word_lst **old_lst,
					t_fd_list *fds, t_redir_list *redirs);
int				sh_pars(t_minish **minish);
bool			builtin_or_command(char *cmd);

/* lst_w_cmd function */
t_w_cmd_list	*get_cmd(t_word_lst **old_lst, t_garbage **gb);

bool			is_amp_error(t_char_lst *lst);
bool			is_pipe_error(t_char_lst *lst);
bool			is_semicolon_error(t_char_lst *lst);
bool			is_backslash_error(t_char_lst *lst);
bool			is_dollar_error(t_char_lst *lst);
bool			is_exclamation_error(t_char_lst *lst);
bool			is_colon_error(t_char_lst *lst);

#endif
