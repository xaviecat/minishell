/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:59:02 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/21 14:17:34 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief return the length of the tabi
 * @param tabi
 * @return length of the tabi
 */
int	length_char_tab(char **tabi)
{
	int	i;

	i = 0;
	while (tabi[i])
		i++;
	return (i);
}

/**
 * @brief copy the content of old_tab in new_tab, except var if it don't find it
 * @param new_tab
 * @param old_tab
 * @param gb
 * @param var
 * @return 1 if it find an error, 0 if not
 */
int	unset_tab(char **new_tab, char **old_tab, t_garbage **gb, char *var)
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

/**
 * @brief checking if the var if valid to be unset
 * @param var
 * @return 1 if it's not valid, otherwise 0
 */
int	verif_char_in_var(char *var)
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

/**
 * @brief checking if the var exist in the tab tabi
 * @param var
 * @param tabi
 * @return 1 if it exist, 0 otherwise
 */
int	check_var_exist(char *var, char **tabi)
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

/**
 * @brief checking if is there an error in the variable we have to unset
 * @param lst
 * @return 2 or 1 if is there an error, 0 otherwise
 */
int	string_is_valid(t_cmd_lst *lst)
{
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
	return (0);
}