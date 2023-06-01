/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:46:20 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/01 16:41:12 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_alloc_envp(t_minish *msh, t_w_cmd_list *content)
{
	size_t	size_count;

	content = content->next;
	while (content)
	{
		
	}
//	msh->envp = ft_malloc(&(msh->garbage))
}

void	b_export(t_minish *msh, t_w_cmd_list *content)
{
	if (!(msh->envp))
		ft_alloc_envp(msh, content);
}