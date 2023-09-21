/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:51:51 by nfaust            #+#    #+#             */
/*   Updated: 2023/09/21 19:08:34 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static size_t	get_arg_count(t_cmd_lst *curr, char **envp)
{
	size_t	size;

	size = 0;
	curr = curr->next;
	while (curr)
	{
		if (not_in_env(curr->cmd, envp))
			size += 1;
		curr = curr->next;
	}
	return (size);
}

static int	contain_dquote(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		if (str[i++] == '"')
			return (1);
	return (0);
}

static void	print_with_backslash(char *str)
{
	size_t	i;

	i = 0;
	printf("=\"");
	while (str[i])
	{
		if (str[i] == '"')
			printf("\\%c", str[i]);
		else
			printf("%c", str[i]);
		i++;
	}
	printf("\"\n");
}

int	ft_alloc_envp(t_msh *msh, t_cmd_lst *curr)
{
	msh->envp = ft_malloc(&(msh->garbage), sizeof(char *),
			get_arg_count(curr, msh->envp) + 1);
	if (!(msh->envp))
		return (0);
	return (1);
}

int	export_print(t_msh *msh)
{
	char	**envp_cpy;
	size_t	i;
	size_t	j;

	envp_cpy = ft_gbtabdup(msh->envp, &(msh->garbage));
	if (!envp_cpy)
		free_and_exit_minish(msh);
	ft_sort_str_arr(envp_cpy);
	i = 0;
	while (envp_cpy[i])
	{
		printf("declare -x ");
		j = 0;
		while (envp_cpy[i][j] && envp_cpy[i][j] != '=')
			printf("%c", envp_cpy[i][j++]);
		if (envp_cpy[i][j] && contain_dquote(envp_cpy[i] + j))
			print_with_backslash(envp_cpy[i] + j + 1);
		else if (envp_cpy[i][j++])
			printf("=\"%s\"\n", envp_cpy[i] + j);
		else
			printf("\n");
		i++;
	}
	return (0);
}
