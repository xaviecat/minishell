/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:05:08 by xcharra           #+#    #+#             */
/*   Updated: 2023/03/16 18:46:54 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str, int fd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (str == NULL)
		return (ft_putstr("(null)", fd));
	while (str[i])
	{
		ret += ft_putchar(str[i], fd);
		i++;
	}
	return (ret);
}
