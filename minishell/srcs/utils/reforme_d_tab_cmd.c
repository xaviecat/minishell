/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reforme_d_tab_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:36:12 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/12 13:39:20 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	count_length_w_cmd(t_w_cmd_list *lst)
{
	int	nb_p_char;

	nb_p_char = 0;
	while (lst)
	{
		nb_p_char++;
		if (lst->next)
			lst = lst->next;
		else
			return (nb_p_char);
	}
	return (nb_p_char);
}

void	complete_tab(char **tabi, t_w_cmd_list **lst, t_garbage **gb, char *cmd)
{
	int				i;
	t_w_cmd_list	*next;

	i = 1;
	tabi[0] = ft_gbstrdup(cmd, gb);
	ft_free(gb, cmd); // ? A voir
	*lst = (*lst)->next;
	while (*lst)
	{
		tabi[i] = ft_gbstrdup((*lst)->cmd, gb);
		next = (*lst)->next;
		ft_free(gb, (*lst)->cmd);
		ft_free(gb, (*lst));
		*lst = next;
		i++;
	}
	tabi[i] = NULL;
}

char	**reforme_d_tab_cmd(t_w_cmd_list **lst, char *cmd, t_garbage **gb)
{
	int		nb_p_char;
	char	**new_d_tab;

	nb_p_char = 0;
	if (!cmd)
		return (NULL);
	nb_p_char = count_length_w_cmd(*lst);
	new_d_tab = ft_malloc(gb, sizeof(char *), nb_p_char + 1);
	complete_tab(new_d_tab, lst, gb, cmd);
	return (new_d_tab);
}
