/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:34:42 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/28 13:20:06 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSGS_H
# define ERROR_MSGS_H

# define MSH			"minishell: "
/* custom errors */
# define UN_QUOTE		"unclosed quote\n"
# define S_AMP			"feature not handled: '&'\n"
# define D_AMP			"feature not handled: '&&'\n"
# define D_PIPE			"feature not handled: '||'\n"
# define SEMICOLON		"feature not handled: ';'\n"
# define BACKSLASH		"feature not handled: '\\'\n"
# define D_DOLLAR		"feature not handled: '$$'\n"
# define S_DOLLAR		"feature not handled: '$"
# define P_OPEN			"feature not handled: '('\n"
# define P_CLOSE		"feature not handled: ')'\n"


# define E_EXPORT		"export: "
# define E_CD			"cd: "
# define E_UNSET		"unset: "
# define E_EXIT			"exit: "

# define TOO_MN_ARGS	"too many arguments\n"
# define CMD_NOT_FOUND	": command not found\n"
# define NT_VAL_ID		": not a valid identifier\n"
# define NO_SFD			": No such file or directory\n"
# define IS_DIR			": Is a directory\n"
# define NO_PERM		": Permission denied\n"
# define NUM_ARG		": numeric argument required\n"

/* bash errors*/
# define S_SM_A_BRA		"syntax error near unexpected token '<'\n"
# define D_SM_A_BRA		"syntax error near unexpected token '<<'\n"
# define S_GR_A_BRA		"syntax error near unexpected token '>'\n"
# define D_GR_A_BRA		"syntax error near unexpected token '>>'\n"
# define NL_TKN			"syntax error near unexpected token 'newline'\n"
# define PIPE_TKN		"syntax error near unexpected token '|'\n"
# define UN_TKN			"syntax error near unexpected token "

#endif
