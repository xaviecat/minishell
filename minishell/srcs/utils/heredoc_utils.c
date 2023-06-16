/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:57:11 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/15 16:38:42 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
		if (!line || !ft_strncmp(line, delimiter, delimiter_len + 1))
			break ;
		heredoc = word_lst_add_back(heredoc, gb, ft_gbstrdup(line, gb));
		if (!heredoc)
			return (free(line), NULL);
		free(line);
	}
	if (g_exit_status == 130 || g_exit_status == 131)
		return (NULL);
	free(line);
	while (heredoc && heredoc->prev)
		heredoc = heredoc->prev;
	return (heredoc);
}

int	expand_heredoc(t_word_lst *heredoc, t_msh *msh)
{
	t_word_lst	*heredoc_cpy;

	heredoc_cpy = heredoc;
	while (heredoc_cpy)
	{
		heredoc_cpy->word = expand_vars(heredoc_cpy->word, msh);
		if (!heredoc_cpy->word)
			return (0);
		heredoc_cpy = heredoc_cpy->next;
	}
	return (1);
}

t_word_lst	*display_heredoc(t_word_lst *heredoc,
							t_msh *msh, t_redir_lst *redirs)
{
	destroy_heredoc(heredoc, &(msh->garbage));
	heredoc = run_heredoc(redirs->filename, &(msh->garbage));
	if ((!heredoc && errno == ENOMEM)
		|| (!does_contain_quotes(redirs->filename)
			&& !expand_heredoc(heredoc, msh)))
		return (NULL);
	return (heredoc);
}
