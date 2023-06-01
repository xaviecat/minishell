/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:08:17 by nfaust            #+#    #+#             */
/*   Updated: 2023/05/31 21:27:24 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief collect the content of the environnement variable
 * @param envp
 * @param var the environnement variable
 * @return the content of the environnement variable, \n\n
 * an allocated string containing "" if the variable is not set
 */
static char	*expand_env_var(t_garbage **gb, char **envp, char *var)
{
	size_t	i;
	size_t	var_len;
	char	*var_expansion;

	if (!envp || !var)
		return (NULL);
	var_len = ft_strlen(var);
	if (var_len == 0)
		return (NULL);
	var_expansion = ft_gbstrjoin(var + 1, "=", gb);
	if (!var_expansion)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i++], var_expansion, var_len) == 0)
		{
			ft_free(gb, var_expansion);
			var_expansion = ft_gb_strdup(envp[i - 1] + var_len, gb);
			if (!var_expansion)
				return (NULL);
			return (var_expansion);
		}
	}
	return (ft_free(gb, var_expansion), ft_gb_strdup("", gb));
}

/**
 * @brief collect the content of the environnement
 * variable and cut spaces in it if needed
 * @param env_var the environnement variable
 * @param double_not_closed 1 if a double quote is opened, \n 0 if not
 * @param envp
 * @return the content of the environnement variable
 */
static char	*set_expanded_env_var(char *env_var, t_minish *msh,
									int double_not_closed)
{
	char	*expanded_env_var;

	expanded_env_var = expand_env_var(&(msh->garbage), msh->envp, env_var);
	if (double_not_closed < 0)
		expanded_env_var = cut_whitespaces(expanded_env_var, NULL);
	if (!expanded_env_var)
		return (ft_free(&(msh->garbage), env_var), NULL);
	return (expanded_env_var);
}

/**
 * @brief modify a cmd from start to whitespace by replacing
 * env vars by their content and reallocating it
 * @param cmd the cmd that you want to expand
 * @param start the index of the $ symbol
 * @param envp
 * @param double_not_closed 1 if a double quote is opened, \n 0 if not
 * @return the modified cmd
 */
static char	*modify_command(char *cmd, t_minish *msh,
							size_t start, int double_not_closed)
{
	char	*env_var;
	char	*exp_env_v;
	char	*m_cmd;

	env_var = ft_gbstrdup_to_charset(cmd + start, " \t\n\v\f\r\"\'\0", &(msh->garbage));
	if (!env_var)
		return (NULL);
	if (is_dollar_alone(env_var, cmd, start))
		return (ft_free(&(msh->garbage), env_var), cmd);
	exp_env_v = set_expanded_env_var(env_var, msh, double_not_closed);
	if (!exp_env_v)
		return (ft_free(&(msh->garbage), env_var),
			ft_free(&(msh->garbage), cmd), NULL);
	m_cmd = fill_mdcmd(cmd, start, exp_env_v, env_var);
	return (ft_free_mcmd(env_var, cmd, exp_env_v, &(msh->garbage)), m_cmd);
}

/**
 * @brief check whether or not a string should be expanded and expand it
 * @param command the string to expand
 * @param envp
 * @return the modified string
 */
static char	*expand_vars(char *command, t_minish *msh)
{
	size_t	i;
	int		double_not_closed;

	i = 0;
	double_not_closed = -1;
	while (command[i])
	{
		if (command[i] == '"')
			double_not_closed *= -1;
		if (command[i] == '$')
		{
			command = modify_command(command, msh, i, double_not_closed);
			if (!command)
				return (NULL);
		}
		if (command[i] && command[i++] == '\'' && double_not_closed < 0)
			while (command[i] && command[i] != '\'')
				i++;
		if (command[i] && command[i] == '\'')
			i++;
	}
	return (command);
}

/**
 * @brief expand parts of commands that needs to be expanded
 * @param w_lst command word list
 * @param envp
 */
void	expand_commands(t_minish *minish)
{
	t_word_lst	*w_lst_cpy;
	char		*command;

	w_lst_cpy = minish->lst_w;
	printf(GREEN"starting expand\n");
	while (w_lst_cpy)
	{
		command = expand_vars(w_lst_cpy->word, minish);
		if (!command)
			return ; // ? code d'erreur a ajouter
		w_lst_cpy->word = ft_gb_strdup(command, &(minish->garbage));
		free(command);
		if (!w_lst_cpy->word)
			return ;
		printf("%s\n", w_lst_cpy->word);
		w_lst_cpy = w_lst_cpy->next;
	}
	printf("expand end\n\n"RESET);
}
