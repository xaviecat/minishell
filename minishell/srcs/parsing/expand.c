/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:08:17 by nfaust            #+#    #+#             */
/*   Updated: 2023/05/16 18:37:22 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/**
 * @brief collect the content of the environnement variable
 * @param envp
 * @param var the environnement variable
 * @return the content of the environnement variable, \n an allocated string containing "" if the variable is not set
 */
static char	*expand_env_var(char **envp, char *var)
{
	size_t	i;
	size_t	var_len;
	char	*var_expansion;

	if (!envp || !var)
		return (NULL);
	var_len = ft_strlen(var);
	if (var_len == 0)
		return (NULL);
	var_expansion = ft_strjoin(var + 1, "=");
	if (!var_expansion)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i++], var_expansion, var_len) == 0)
		{
			free(var_expansion);
			var_expansion = ft_strdup(envp[i - 1] + var_len);
			if (!var_expansion)
				return (NULL);
			return (var_expansion);
		}
	}
	return (free(var_expansion), ft_strdup(""));
}

/**
 * @brief collect the content of the environnement variable and cut spaces in it if needed
 * @param env_var the environnement variable
 * @param double_not_closed 1 if a double quote is opened, \n 0 if not
 * @param envp
 * @return the content of the environnement variable
 */
static char *set_expanded_env_var(char *env_var, int double_not_closed, char **envp)
{
	char	*expanded_env_var;

	expanded_env_var = expand_env_var(envp, env_var);
	if (double_not_closed < 0)
		expanded_env_var = cut_whitespaces(expanded_env_var);
	if (!expanded_env_var)
		return (free(env_var), NULL);
	return (expanded_env_var);
}

/**
 * @brief modify a cmd from start to whitespace by replacing env vars by their content and reallocating it
 * @param cmd the cmd that you want to expand
 * @param start the index of the $ symbol
 * @param envp
 * @param double_not_closed 1 if a double quote is opened, \n 0 if not
 * @return the modified cmd
 */
static char	*modify_command(char *cmd,
							size_t start, char **envp, int double_not_closed)
{
	char	*env_var;
	char	*exp_env_v;
	char	*m_cmd;
	size_t	i;

	env_var = ft_strdup_to_charset(cmd + start, " \t\n\v\f\r\"\'\0");
	if (!env_var)
		return (NULL);
	if (is_dollar_alone(env_var, cmd, start))
		return (free(env_var), cmd);
	exp_env_v = set_expanded_env_var(env_var, double_not_closed, envp);
	if (!exp_env_v)
		return (free(env_var), NULL);
	m_cmd = malloc(sizeof(char) * (ft_strlen(cmd) + 1
				+ (ft_strlen(exp_env_v) - ft_strlen(env_var))));
	if (!m_cmd)
		return (free(env_var), free(exp_env_v), NULL);
	str_cpy_to_x(cmd, m_cmd, '$');
	i = 0;
	while (exp_env_v[i])
		m_cmd[start++] = exp_env_v[i++];
	i = (start - i) + ft_strlen(env_var);
	while (cmd[i])
		m_cmd[start++] = cmd[i++];
	return (m_cmd[start] = 0, free(env_var), free(cmd), free(exp_env_v), m_cmd);
}

/**
 * @brief check whether or not a string should be expanded and expand it
 * @param command the string to expand
 * @param envp
 * @return the modified string
 */
static char	*expand_vars(char *command, char **envp)
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
			command = modify_command(command, i, envp, double_not_closed);
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
void	expand_commands(t_word_lst **w_lst, char **envp)
{
	t_word_lst	*w_lst_cpy;

	w_lst_cpy = *w_lst;
	//printf("starting expand\n");
	while (w_lst_cpy)
	{
		w_lst_cpy->word = expand_vars(w_lst_cpy->word, envp);
		if (!w_lst_cpy->word)
			return ; // ? code d'erreur a ajouter
	//	printf("%s\n", w_lst_cpy->word);
		w_lst_cpy = w_lst_cpy->next;
	}
}

/*
		TO DO LIST
- gerer les differences entre "$USER" et $USER (whitespaces a skip pour $USER)
- envoyer differents caracteres pour les quotes a garder et celles a supprimer
*/