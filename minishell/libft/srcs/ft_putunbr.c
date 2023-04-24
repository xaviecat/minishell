/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:21:24 by xcharra           #+#    #+#             */
/*   Updated: 2023/03/16 18:47:13 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr(unsigned int nb, int fd)
{
	char	c;
	int		ret;

	c = '0';
	ret = 0;
	if (nb < 10)
		ret += ft_putchar(nb + c, fd);
	if (nb >= 10)
	{
		ret += ft_putunbr(nb / 10, fd);
		ret += ft_putunbr(nb % 10, fd);
	}
	return (ret);
}
