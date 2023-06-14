/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:35:07 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/14 17:29:39 by nfaust           ###   ########.fr       */
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

t_word_lst	*display_heredoc(char *delimiter, t_garbage **gb)
{
	t_word_lst	*heredoc;
	char		*line;
	size_t		delimiter_len;

	line = readline("> ");
	heredoc = word_lst_new(line, gb);
	delimiter = remove_quotes(delimiter, gb);
	if (!delimiter || !heredoc)
		return (NULL);
	ft_free(gb, line);
	line = readline("> ");
	delimiter_len = ft_strlen(delimiter);
	while (ft_strncmp(line, delimiter, delimiter_len))
	{
		heredoc->next = word_lst_new(line, gb);
		if (!heredoc->next)
			return (NULL);
		heredoc->next->prev = heredoc;
		heredoc = heredoc->next;
		ft_free(gb, line);
		line = readline("> ");
	}
	while (heredoc->prev)
		heredoc = heredoc->prev;
	return (ft_free(gb, line), heredoc);
}

int	expand_heredoc(t_word_lst *heredoc, t_minish *msh)
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

void destroy_heredoc(t_word_lst *heredoc, t_garbage **gb)
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

int	heredoc_handling(t_minish *msh)
{
	t_cmd_list		*cmds;
	t_redir_list	*redirs;
	t_word_lst		*heredoc;

	cmds = msh->cmds;
	while (cmds)
	{
		redirs = cmds->redirs;
		heredoc = NULL;
		while (redirs)
		{
			if (redirs->redir == inin)
			{
				destroy_heredoc(heredoc, &(msh->garbage));
				heredoc = display_heredoc(redirs->filename, &(msh->garbage));
				if (!heredoc || (!does_contain_quotes(redirs->filename)
						&& !expand_heredoc(heredoc, msh)))
					return (0);
			}
			redirs = redirs->next;
		}
		msh->cmds->heredoc = heredoc;
		cmds = cmds->next;
	}
	return (1);
}
