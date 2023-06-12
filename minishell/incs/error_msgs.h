/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:34:42 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/12 17:12:51 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSGS_H
# define ERROR_MSGS_H

/* custom errors */
# define UN_QUOTE		"minishell: unclosed quote\n"
# define S_AMP			"minishell: feature not handled: '&'\n"
# define D_AMP			"minishell: feature not handled: '&&'\n"
# define D_PIPE			"minishell: feature not handled: '||'\n"
# define SEMICOLON		"minishell: feature not handled: ';'\n"
# define BACKSLASH		"minishell: feature not handled: '\\'\n"
# define D_DOLLAR		"minishell: feature not handled: '$$'\n"
# define S_DOLLAR(x)	"minishell: feature not handled: " #x "\n"

# define CMD_NOT_FOUND	": command not found\n"

/* bash errors*/
# define S_SM_A_BRA	"minishell: syntax error near unexpected token '<'\n"
# define D_SM_A_BRA	"minishell: syntax error near unexpected token '<<'\n"
# define S_GR_A_BRA	"minishell: syntax error near unexpected token '>'\n"
# define D_GR_A_BRA	"minishell: syntax error near unexpected token '>>'\n"
# define NL_TKN		"minishell: syntax error near unexpected token 'newline'\n"
# define PIPE_TKN	"minishell: syntax error near unexpected token '|'\n"

# define UN_TKN(x)	"minishell: syntax error near unexpected token " #x "\n"
# define IS_DIR(x)	"minishell: " #x ": Is a directory\n"

#endif
