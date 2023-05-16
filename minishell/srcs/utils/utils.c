/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:01:30 by nfaust            #+#    #+#             */
/*   Updated: 2023/05/15 14:42:11 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*ft_strdup_to_x(char *str, char x)
{
	size_t	new_str_len;
	size_t	i;
	char	*new_str;

	new_str_len = 0;
	i = 0;
	while (str[i] && str[i] != x)
		new_str_len++;
	new_str = malloc(sizeof(char) * (new_str_len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != x)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

int	iswhitespace(int c)
{
	if (c == 32 || c == 9 || c == 10)
		return (1);
	else
		return (0);
}