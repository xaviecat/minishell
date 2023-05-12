/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:10:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/12 18:39:54 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	process_quotes(t_char_lst *lst)
{
	t_char_lst	*tmp;
	int			i;
//	bool		sq;
//	bool		dq;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (i == 0)
		{
			if (tmp->c == '\'')
			{
				tmp->quote = true;
				tmp = tmp->next;
//				i++;
			}
			else if (tmp->c == '\"')
			{
				tmp->d_quote = true;
				tmp = tmp->next;
//				i++;
			}
			else
				tmp = tmp->next;
		}
		else
		{
			if (tmp->prev->d_quote == false && tmp->c == '\'')
			{
				while (tmp && tmp->prev->c != '\'')
				{
					tmp->quote = true;
					tmp = tmp->next;
//					i++;
				}
			}
			else if (tmp->prev->quote == false && tmp->c == '\"')
			{
				while (tmp && tmp->prev->c != '\"')
				{
					tmp->d_quote = true;
					tmp = tmp->next;
//					i++;
				}
			}
			else
				tmp = tmp->next;
		}
		i++;
	}
	ft_fdprintf(2, "{{{{{{{{%i}}}}}}}}", i);
}

/*
 * if "\'"
 * 	set quote true an sq true
 * 	while sq true && tmp->c != '\''
 * 	set quote true
 *
 *
 *  salut 'salut' cava "" '' "'"' '"'"
 *  boucle dans le der else if
 *  cuz if (true et '\"' ok )mais ne peux entre dans le while
 * */