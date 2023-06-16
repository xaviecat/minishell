/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:15:43 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/15 15:23:23 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"

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
}	t_type_char;

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
}	t_type_word;

typedef enum e_type_redir
{
	in,
	inin,
	out,
	outout
}	t_type_redir;

/* structure */
typedef struct s_garbage_lst
{
	void					*content;
	struct s_garbage_lst	*next;
	struct s_garbage_lst	*prev;
}	t_garbage_lst;

typedef struct s_garbage
{
	t_garbage_lst	*first;
	t_garbage_lst	*last;
}	t_garbage;

typedef struct s_redir_lst
{
	t_type_redir		redir;
	char				*filename;
	struct s_redir_lst	*next;
	struct s_redir_lst	*last_added;
}	t_redir_lst;

typedef struct s_fd_lst
{
	int				in;
	int				out;
	struct s_fd_lst	*next;
	struct s_fd_lst	*last_added;
}	t_fd_lst;

typedef struct s_cmd_lst
{
	char				*cmd;
	bool				s_quote;
	bool				d_quote;
	struct s_cmd_lst	*next;
	struct s_cmd_lst	*last_added;
}	t_cmd_lst;

typedef struct s_node_lst
{
	t_cmd_lst			*lst_cmd;
	char				*cmdpath;
	char				**cmdtab;
	bool				builtin;
	pid_t				pid;
	struct s_redir_lst	*redirs;
	struct s_word_lst	*heredoc;
	struct s_fd_lst		*fds;
	struct s_node_lst	*next;
	struct s_node_lst	*previous;
	struct s_node_lst	*last_added;
}	t_node_lst;

typedef struct s_word_lst
{
	char				*word;
	t_type_word			type;
	struct s_word_lst	*next;
	struct s_word_lst	*prev;
	struct s_word_lst	*last_added;
}	t_word_lst;

typedef struct s_char_lst
{
	int					pipe;
	char				c;
	t_type_char			type;
	bool				s_quote;
	bool				d_quote;
	struct s_char_lst	*prev;
	struct s_char_lst	*next;
	struct s_char_lst	*last_added;
}	t_char_lst;

typedef struct s_msh
{
	char		**envp;
	int			prev_pipe[2];
	int			curr_pipe[2];
	t_char_lst	*lst_c;
	t_word_lst	*lst_w;
	t_node_lst	*lst_n;
	t_garbage	*garbage;
}	t_msh;

#endif
