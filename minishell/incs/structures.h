/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
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

/* structure */
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
	char				*cmdpath; // strjoin PATH+CMD
	char				**cmdtab;
	bool				builtin;
	struct s_redir_list	*redirs;
	struct s_word_lst	*heredoc;
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


#endif
