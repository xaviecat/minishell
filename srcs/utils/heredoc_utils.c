/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:57:11 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/09 19:19:04 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/***
 * @brief removes quotes from the delimiter
 * @param str
 * @param gb
 * @return the delimiter without quotes
 */
char	*remove_quotes(char *str, t_garbage **gb)
{
	size_t	i;
	size_t	j;
	size_t	counter;
	char	*str_without_quotes;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			counter++;
		i++;
	}
	str_without_quotes = ft_malloc(gb, sizeof(char), counter + 1);
	if (!str_without_quotes)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			str_without_quotes[j++] = str[i];
		i++;
	}
	return (str_without_quotes[j] = 0, str_without_quotes);
}

/***
 * @brief destroys and frees the heredoc
 * @param heredoc
 * @param gb
 */
void	destroy_heredoc(t_word_lst *heredoc, t_garbage **gb)
{
	if (!heredoc)
		return ;
	while (heredoc)
	{
		ft_free(gb, heredoc->word);
		if (heredoc->next == NULL)
			break ;
		heredoc = heredoc->next;
	}
	while (heredoc->prev)
	{
		heredoc = heredoc->prev;
		ft_free(gb, heredoc->next);
	}
	ft_free(gb, heredoc);
}

/**
 * @brief checks if the inputed line matches the delimiter or
 * if the allocation of the line has failed,
 * and prints a \\n if a ctrl-D was sent by the user
 * @return 0 if the input is correct and no allocation error was found \n
 * 1 else
 */
static int	check_line(char *line, char *delimiter, ssize_t delimiter_len)
{
	if (!line && errno != ENOMEM)
		ft_fdprintf(2, MSH WARN_HD"(wanted '%s')\n", delimiter);
	if (!line || !ft_strncmp(line, delimiter, delimiter_len + 1))
		return (1);
	return (0);
}

/***
 * @brief executes the heredoc and displays a new line while delimiter
 * is not entered
 * @param delimiter
 * @param gb
 * @return the heredoc content. NULL if nothing is inputted
 */
t_word_lst	*run_heredoc(char *delimiter, t_garbage **gb)
{
	t_word_lst	*heredoc;
	char		*line;
	size_t		delimiter_len;

	delimiter = remove_quotes(delimiter, gb);
	if (!delimiter)
		return (NULL);
	delimiter_len = ft_strlen(delimiter);
	heredoc = NULL;
	signal_hub_heredoc();
	while (g_exit_status != 130)
	{
		line = readline("> ");
		if (check_line(line, delimiter, delimiter_len))
			break ;
		heredoc = word_lst_add_back(heredoc, gb, ft_gbstrdup(line, gb));
		if (!heredoc)
			return (free(line), NULL);
		free(line);
	}
	if (g_exit_status == 130 || g_exit_status == 131)
		return (NULL);
	while (heredoc && heredoc->prev)
		heredoc = heredoc->prev;
	return (free(line), heredoc);
}

/***
 * @brief expands the content of the heredoc if needed
 * @param heredoc
 * @param msh
 * @return 1 on success, 0 on failure
 */
int	expand_heredoc(t_word_lst *heredoc, t_msh *msh)
{
	t_word_lst	*heredoc_cpy;

	heredoc_cpy = heredoc;
	while (heredoc_cpy)
	{
		heredoc_cpy->word = expand_vars(heredoc_cpy->word, msh, 1);
		if (!heredoc_cpy->word)
			return (0);
		heredoc_cpy = heredoc_cpy->next;
	}
	return (1);
}
