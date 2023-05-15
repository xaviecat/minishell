/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:08:17 by nfaust            #+#    #+#             */
/*   Updated: 2023/05/15 19:11:13 by nfaust           ###   ########.fr       */
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
		if (ft_strncmp(envp[i], var_expansion, var_len) == 0)
		{
			free(var_expansion);
			var_expansion = ft_strdup(envp[i] + var_len);
			if (!var_expansion)
				return (NULL);
			return (var_expansion);
		}
		i++;
	}
	return (ft_strdup(""));
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
 * @brief modify a command from start to whitespace by replacing env vars by their content and reallocating it
 * @param command the command that you want to expand
 * @param start the index of the $ symbol
 * @param envp
 * @param double_not_closed 1 if a double quote is opened, \n 0 if not
 * @return the modified command
 */
static char	*modify_command(char *command, size_t start, char **envp, int double_not_closed)
{
	char	*env_var;
	char	*expanded_env_var;
	char	*m_cmd;
	size_t	i;

	env_var = ft_strdup_to_charset(command + start, " \t\n\v\f\r\"\'\0");
	if (!env_var)
		return (NULL);
	if (ft_strncmp(env_var, "$", 2) == 0)
		return (free(env_var), command);
	expanded_env_var = set_expanded_env_var(env_var, double_not_closed, envp);
	if (!expanded_env_var)
		return (free(env_var), NULL);
	m_cmd = malloc(sizeof(char) * (ft_strlen(command)
				+ (ft_strlen(expanded_env_var) - ft_strlen(env_var))));
	if (!m_cmd)
		return (free(env_var), free(expanded_env_var), NULL);
	str_cpy_to_x(command, m_cmd, '$');
	i = 0;
	while (expanded_env_var[i])
		m_cmd[start++] = expanded_env_var[i++];
	i = (start - i) + ft_strlen(env_var);
	while (command[i])
		m_cmd[start++] = command[i++];
	m_cmd[start] = 0;
	return (free(env_var), free(command), free(expanded_env_var), m_cmd);
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
		if (command[i++] == '\'' && double_not_closed < 0)
			while (command[i] && command[i] != '\'')
				i++;
		if (command[i] == '\'')
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
	printf("starting expand\n");
	while (w_lst_cpy)
	{
		w_lst_cpy->word = expand_vars(w_lst_cpy->word, envp);
		if (!w_lst_cpy->word)
			return ; // ? code d'erreur a ajouter
		printf("%s\n", w_lst_cpy->word);
		w_lst_cpy = w_lst_cpy->next;
	}
}

/*
		TO DO LIST
- gerer les differences entre "$USER" et $USER (whitespaces a skip pour $USER)
- envoyer differents caracteres pour les quotes a garder et celles a supprimer
*/