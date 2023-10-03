/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:08:17 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/03 13:38:58 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	negativization(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			str[i] = (char)((int) str[i] * -1);
		i++;
	}
}

/**
 * @brief modify a lst_cmd from start to whitespace by replacing
 * env vars by their content and reallocating it
 * @param cmd the lst_cmd that you want to expand
 * @param start the index of the $ symbol
 * @param envp
 * @param double_not_closed 1 if a double quote is opened, \n 0 if not
 * @return the modified lst_cmd
 */
static char	*modify_command(char *cmd, t_msh *msh,
							size_t start, int double_not_closed)
{
	char	*env_var;
	char	*exp_env_v;
	char	*m_cmd;

	env_var = ft_cut_var(cmd + start, &(msh->garbage));
	if (!env_var)
		return (NULL);
	if (is_dollar_alone(env_var, cmd, start, double_not_closed))
		return (ft_free(&(msh->garbage), env_var), cmd);
	exp_env_v = set_expanded_env_var(env_var, msh, double_not_closed);
	if (!exp_env_v)
		return (ft_free(&(msh->garbage), env_var),
			ft_free(&(msh->garbage), cmd), NULL);
	negativization(exp_env_v);
	m_cmd = fill_mdcmd(cmd, start, exp_env_v, env_var);
	if (add_to_garbage(&(msh->garbage), m_cmd))
		return (free(m_cmd), NULL);
	return (ft_free_mcmd(env_var, cmd, exp_env_v, &(msh->garbage)), m_cmd);
}

/**
 * @brief check whether or not a string should be expanded and expand it
 * @param command the string to expand
 * @param envp
 * @return the modified string
 */
char	*expand_vars(char *command, t_msh *msh)
{
	size_t	i;
	int		double_not_closed;

	i = 0;
	double_not_closed = -1;
	while (command[i])
	{
		if (command[i] == '"')
			double_not_closed *= -1;
		if (command[i] == '$' && command[i + 1] && !ft_isalpha(command[i + 1])
			&& !ft_strchr("?'\"", command[i + 1]))
			i++;
		if (command[i] == '$')
		{
			command = modify_command(command, msh, i, double_not_closed);
			if (!command)
				return (NULL);
		}
		if (command[i] && command[i++] == '\'' && double_not_closed < 0)
			while (command[i] && (command[i] != '\'' || !i++))
				i++;
	}
	return (command);
}

/**
 * @brief expand parts of commands that needs to be expanded
 * @param w_lst command word list
 * @param envp
 */
int	expand_commands(t_msh *msh)
{
	t_word_lst	*w_lst_cpy;

	w_lst_cpy = msh->lst_w;
	while (w_lst_cpy)
	{
		if (!ft_strncmp(w_lst_cpy->word, "\"\"", 3))
			w_lst_cpy->is_nill = true;
		if (w_lst_cpy->type != delimiteur)
			w_lst_cpy->word = expand_vars(w_lst_cpy->word, msh);
		if (!w_lst_cpy->word)
			free_and_exit_minish(msh, NULL);
		w_lst_cpy = w_lst_cpy->next;
	}
	return (1);
}
