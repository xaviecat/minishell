/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_filename.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:29:55 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/26 17:29:55 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief reallocates filename and deletes quote from it
 * @return 1 on success \n 0 on allocation error
 */
static int	del_quote_redir(t_redir_lst **lst, t_garbage **gb)
{
	char	*new_filename;
	size_t	new_filename_len;

	new_filename_len = get_newcmd_len((*lst)->filename) + 1;
	new_filename = ft_malloc(gb, sizeof(char), new_filename_len);
	if (!new_filename)
		return (0);
	(*lst)->filename = modify_cmd((*lst)->filename, new_filename, gb);
	return (1);
}

/**
 * @brief find out if filename have quotes in it and delete them from filename
 * @return 1 on success \n 0 on allocation error
 */
int	del_quote_filename(t_redir_lst **lst, t_garbage **gb)
{
	t_redir_lst	*first;

	first = *lst;
	while (*lst)
	{
		if (ft_strchr((*lst)->filename, '\'') != NULL
			|| ft_strchr((*lst)->filename, '"') != NULL)
		{
			if (!(del_quote_redir(lst, gb)))
				return (0);
		}
		*lst = (*lst)->next;
	}
	*lst = first;
	return (1);
}
