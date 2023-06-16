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


# include "colors.h"
# include "error_msgs.h"
# include "../libft/incs/libft.h"

/* malloc, free, exit, getenv, tcsetattr, tcgetattr, */
# include <stdlib.h>

/* open */
# include <fcntl.h>

/* close, read, write, access, dup, dup2, execve, fork, pipe, unlink
, rl_*, getcwd, chdir, stat, lstat, fstat, isatty, ttyname,ttyslot */
# include <unistd.h>
# include <sys/stat.h>

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

# include "structures.h"

extern int		g_exit_status;

typedef bool	(*t_unhandled_tab)(t_char_lst *);
typedef int		(*t_builtin_tab)();

/* global */
void			free_and_exit_minish(t_msh *minish, char ***envp_sh);
void			print_bannier(void);
t_msh			*create_minishell(char **envp, char **envp_sh);
/* parsing */
int				parsing_char(t_msh **minish, char *line, char **envp_sh);
int				parsing_word(t_msh **minish, char **envp_sh);
int				parsing_cmd(t_msh **minish, char **envp_sh);
char			**parsing_argu(char *arg_term);
t_msh			*parsing_command(char *cmd_line, t_msh *sh);
int				expand_commands(t_msh *msh);
char			*cut_whitespaces(char *str, t_garbage **gb);
bool			process_quotes(t_char_lst *lst);
void			harmonize_spaces(t_char_lst **lst, t_garbage **gb);
int				redir_is_valid(t_word_lst **lst, t_garbage **gb);
int				check_pipe_and_redir(t_garbage **gb, t_word_lst **lst);
char			**reforme_d_tab_cmd(t_cmd_lst **lst, char *cmd, t_garbage **gb);
int				ft_del_quotes(t_msh *msh);

/* redir */
t_redir_lst		*get_redir(t_word_lst **lst, t_garbage **gb);
void			print_redir(t_redir_lst *lst);
void			free_error_redir(t_garbage **gb, t_redir_lst **lst);
void			redir_add_back(t_redir_lst **lst, t_redir_lst *new);
t_redir_lst		*redir_last(t_redir_lst *lst);
t_redir_lst		*new_redir(t_type_redir type_red, t_garbage **gb);

/* fds */
t_fd_lst		*create_fds_list(t_redir_lst *redirs, t_garbage **gb);
void			print_fd(t_fd_lst *lst);
void			free_error_fds(t_garbage **gb, t_fd_lst **lst);
t_fd_lst		*new_fds(t_garbage **gb);
void			fds_add_back(t_fd_lst **lst, t_fd_lst *new);

/* error */
bool			is_forbidden_char(t_char_lst *lst);
bool			unhandled_char(t_char_lst *lst);
bool			is_bad_redir(t_char_lst *lst);
void			free_error_word_lst(t_garbage **gb, t_word_lst **lst);

/* builtins */
void			b_pwd(char **envp);
void			b_cd(t_cmd_lst *cmd, t_msh *msh);
void			b_echo(t_cmd_lst *content);
void			b_exit(t_msh *msh);
int				b_export(t_msh *msh, t_cmd_lst *cmds);
void			b_env(char **env);
int				b_unset(t_msh *sh);
int				find_builtin(t_msh *sh);

/* exec */
int				exec_all(t_msh *msh);
void			get_access(t_msh **sh);

/* signal */
void			signal_handler(int signum);
void			signal_term(int signum);
void			signal_heredoc(int signum);
void			signal_exec(int signum);
void			signal_hub_term(void);
void			signal_hub_heredoc(void);
void			signal_hub_exec(void);

/* utils */
char			*ft_cut_var(char *str, t_garbage **gb);
int				ft_isspace(char c);
char			*str_cpy_to_x(char *src, char *dst, char x);
int				is_dollar_alone(char *env_var, char *cmd, size_t start);
void			*ft_malloc(t_garbage **garbage, int the_size, int number);
void			ft_free_all(t_garbage **lst);
void			ft_free(t_garbage **lst, void *content);
t_garbage_lst	*new_garbage(void *content);
t_garbage		*create_garbage_container(void);
void			garbage_add_back(t_garbage_lst **lst, t_garbage_lst *new);
char			*ft_gbstrdup(const char *src, t_garbage **gb);
void			get_first_garbage(t_garbage **lst);
char			*ft_gbstrjoin(char const *s1, char const *s2, t_garbage **gb);
void			ft_free_mcmd(char *env_var, char *cmd,
					char *exp_env_var, t_garbage **gb);
char			*fill_mdcmd(char *cmd, size_t start,
					char *exp_env_v, char *env_var);
void			*ft_gbcalloc(size_t count, size_t size, t_garbage **gb);
char			*ft_gbstrtrim(char const *s1, char const *set, t_garbage **gb);
char			**ft_gbtabdup(char **dbtab, t_garbage **gb);
void			ft_tabfree(char **tbl);
void			ft_gbtabfree(char **tbl, t_garbage **gb);
char			**ft_gbtabjoin(char **tab1, char **tab2, t_garbage **gb);
//void			ft_gbfree_tab(char **tab_to_free, t_garbage **gb); //! supprimer remplacer par ft_gbtabfree
int				not_in_env(char *cmd, char **envp);
int				modify_envp(char *cmd, char **envp, t_garbage **gb);
void			ft_sort_str_arr(char **str_arr);
char			**ft_gbsplit(char const *s, char c, t_garbage **gb);
char			*ft_gbsubstr(char const *s,
					unsigned int start, size_t len, t_garbage **gb);
int				is_concat(char *cmd);

/* list_char function */
t_char_lst		*char_lst_new(char c, t_garbage **gb);
t_char_lst		*char_lst_last(t_char_lst *lst);
void			char_lst_add_back(t_char_lst **lst, t_char_lst *new);
void			char_lst_add_front(t_char_lst **lst, t_char_lst *new);
int				create_char_lst_with_c_inside(char *cmd_line, t_msh **sh);
void			give_type_in_lst(t_char_lst **lst);
void			print_lst_char(t_char_lst *lst);
void			char_lst_delone(t_char_lst **lst, t_garbage **gb);

/* lst_word function */
int				create_word_lst(t_msh **sh);
void			print_lst_word(t_word_lst *lst);
t_type_word		is_a_bultin(char *word);
t_type_word		get_cat_of_word(char *word);
void			word_lst_delone(t_word_lst **lst, t_garbage **gb);
t_word_lst		*word_lst_first(t_word_lst *lst);
void			get_other_type_word(t_word_lst **lst);
t_word_lst		*word_lst_new(char *word, t_garbage **gb);
t_word_lst		*word_lst_add_back(t_word_lst *wlst, t_garbage **gb,
					char *word);

/* list command maybe not useful */
t_node_lst		*lst_cmd_new(t_cmd_lst *cmds,
							   t_fd_lst *fds, t_redir_lst *redir, t_garbage **gb);
void			lst_cmd_add_back(t_node_lst **lst, t_node_lst *new);
void			print_lst_cmd(t_node_lst *lst);
void			lst_clear(t_node_lst **lst);
t_node_lst		*create_lst_cmd(t_word_lst **old_lst,
								  t_fd_lst *fds, t_redir_lst *redirs);
int				sh_pars(t_msh **msh);

t_builtin builtin_or_command(char *cmd);

/* lst_w_cmd function */
t_cmd_lst	*get_cmd(t_word_lst **old_lst, t_garbage **gb);

bool			is_amp_error(t_char_lst *lst);
bool			is_pipe_error(t_char_lst *lst);
bool			is_semicolon_error(t_char_lst *lst);
bool			is_backslash_error(t_char_lst *lst);
bool			is_dollar_error(t_char_lst *lst);
bool			is_exclamation_error(t_char_lst *lst);
bool			is_colon_error(t_char_lst *lst);

/* heredoc */
int				heredoc_handling(t_msh *msh);
t_word_lst		*display_heredoc(t_word_lst *heredoc,
					t_msh *msh, t_redir_lst *redirs);
int				expand_heredoc(t_word_lst *heredoc, t_msh *msh);


/* A RANGER LOL */
char			*expand_vars(char *command, t_msh *msh);
int				does_contain_quotes(char *str);


/* excution */
void			execution(t_msh *msh);

#endif
