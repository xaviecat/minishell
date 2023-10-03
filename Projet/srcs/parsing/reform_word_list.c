/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reform_word_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:32:39 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/03 15:25:55 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	modify_word(char *new_word, t_word_lst *wlst, t_garbage **gb)
{
	ft_free(gb, wlst->word);
	wlst->word = new_word;
}

static t_word_lst	*convert_str_tab(char **content, t_word_lst *wlst, t_garbage **gb)
{
	size_t		i;

	i = 0;
	while (content[i])
	{
		if (!i)
			modify_word(content[i], wlst, gb);
		else
		{
			if (!word_lst_insert(wlst, gb, content[i]))
				return (NULL);
		}
		i++;
		printf("%s\n", wlst->word);
		wlst = wlst->next;
	}
	ft_fdprintf(2, "%s, %s\n", wlst->word, content[i - 1]);
	ft_free(gb, content);
	return (wlst);
}

int	reform_word_list(t_msh *msh)
{
	t_word_lst	*word_lst_cpy;
	char		**content;

	word_lst_cpy = msh->lst_w;
	while (word_lst_cpy)
	{
		content = ft_gbsplit(word_lst_cpy->word, ' ', &(msh->garbage));
		if (!content)
			return (-1);
		word_lst_cpy = convert_str_tab(content, word_lst_cpy, &(msh->garbage));
		if (!word_lst_cpy)
			return (-1);
		printf("[%s]\n", word_lst_cpy->word);
	}
	return (1);
}