/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:43:43 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/21 11:20:52 by syluiset         ###   ########.fr       */
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

static int	verif_char_in_var(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (ft_fdprintf(2, MSH E_UNSET "%s" NT_VAL_ID, var), 1);
		i++;
	}
	return (0);
}

static int	check_var_exist(char *var, char **tabi)
{
	int	i;

	i = 0;

	while (tabi[i])
	{
		if (ft_strncmp(var, tabi[i], ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	string_exist_and_valid(t_cmd_lst *lst)
{
	t_cmd_lst	*first;

	first = lst;
	while (lst)
	{
		if (lst->cmd[0] == '-')
			return (ft_fdprintf(2, MSH E_UNSET "%s " INV_OPT, lst->cmd), 2);
		if (lst->cmd[0] == '\0')
			return (ft_fdprintf(2, MSH E_UNSET "%s" NT_VAL_ID, lst->cmd), 1);
		if (ft_isdigit(lst->cmd[0]))
			return (ft_fdprintf(2, MSH E_UNSET "%s" NT_VAL_ID, lst->cmd), 1);
		if (verif_char_in_var(lst->cmd))
			return (1);
		if (ft_strncmp(lst->cmd, "-", 1) == 0)
			return (ft_fdprintf(2, MSH E_UNSET INV_OPT), 2);
		if (lst->next)
			lst = lst->next;
		else
			break ;
	}
	lst = first;
	return (3);
}

int	b_unset(t_msh *sh)
{
	char	**old_envp;
	char	*name_var;
	int		ret_error;

	if (!sh->lst_n->lst_cmd->next)
		return (0);
	sh->lst_n->lst_cmd = sh->lst_n->lst_cmd->next;
	ret_error = string_exist_and_valid(sh->lst_n->lst_cmd);
	if (ret_error != 3)
		return (ret_error);
	while (sh->lst_n->lst_cmd)
	{
		name_var = ft_gbstrdup(sh->lst_n->lst_cmd->cmd, &(sh->garbage));
		check_var_exist(name_var, sh->envp);
		old_envp = ft_gbtabdup(sh->envp, &(sh->garbage));
		if (!old_envp && errno == ENOMEM)
			return (ENOMEM);
		ft_gbtabfree(sh->envp, &(sh->garbage));
		sh->envp = ft_malloc(&(sh->garbage), sizeof(char *),
				length_char_tab(old_envp) + 1);
		unset_tab(sh->envp, old_envp, &(sh->garbage), name_var);
		ft_free(&(sh->garbage), name_var);
		sh->lst_n->lst_cmd = sh->lst_n->lst_cmd->next;
	}
	return (0);
}
