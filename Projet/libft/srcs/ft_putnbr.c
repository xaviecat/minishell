/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:06:58 by xcharra           #+#    #+#             */
/*   Updated: 2023/03/16 18:47:26 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int nb, int fd)
{
	char	c;
	int		ret;

	c = '0';
	ret = 0;
	if (nb == -2147483648)
	{
		ret += ft_putstr(MININT, fd);
		return (ret);
	}
	if (nb < 0)
	{
		nb = nb * -1;
		ret += ft_putchar('-', fd);
	}
	if (nb >= 0 && nb < 10)
		ret += ft_putchar(nb + c, fd);
	if (nb >= 10)
	{
		ret += ft_putnbr(nb / 10, fd);
		ret += ft_putnbr(nb % 10, fd);
	}
	return (ret);
}
