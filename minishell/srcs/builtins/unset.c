/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:43:43 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/16 10:36:10 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	length_char_tab(char **tabi)
{
	int	i;

	i = 0;
	while (tabi[i])
		i++;
	return (i);
}

static int	unset_tab(char **new_tab, char **old_tab, t_garbage **gb, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!new_tab && errno == ENOMEM)
	{
		ft_free_all(gb);
		return (1);
	}
	while (old_tab[i])
	{
		if (ft_strncmp(old_tab[i], var, ft_strlen(var)) == 0)
			i++;
		else
		{
			new_tab[j] = ft_gbstrdup(old_tab[i], gb);
			i++;
			j++;
		}
		ft_free(gb, old_tab[i - 1]);
	}
	new_tab[j] = NULL;
	return (0);
}


static int	check_var_exist_and_valid(char *var, char **tabi)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (!ft_isalnum(var[i]))
		{
			ft_fdprintf(2, NT_VAL_ID('%s'), var);
			return (0);
		}
		i++;
	}
	i = 0;
	while (tabi[i])
	{
		if (ft_strncmp(var, tabi[i], ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	b_unset(t_minish *sh)
{
	char	**old_envp;
	char	*name_var;

	if (!sh->cmds->cmd->next->cmd)
		return (0);
	name_var = ft_gbstrdup(sh->cmds->cmd->next->cmd, &(sh->garbage));
	if (!check_var_exist_and_valid(name_var, sh->envp))
		return (0);
	old_envp = ft_gbtabdup(sh->envp, &(sh->garbage));
	if (!old_envp && errno == ENOMEM)
		return (1);
	ft_gbtabfree(sh->envp, &(sh->garbage));
	sh->envp = ft_malloc(&(sh->garbage), sizeof(char *),
			length_char_tab(old_envp));
	unset_tab(sh->envp, old_envp, &(sh->garbage), name_var);
	ft_free(&(sh->garbage), name_var);
	return (0);
}
