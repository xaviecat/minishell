/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:30:48 by xcharra           #+#    #+#             */
/*   Updated: 2023/03/16 18:47:32 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(size_t nb, char *base, int fd)
{
	int		ret;

	ret = 0;
	if (nb < 16)
		ret += ft_putchar(base[nb], fd);
	if (nb >= 16)
	{
		ret += ft_putnbr_base(nb / 16, base, fd);
		ret += ft_putnbr_base(nb % 16, base, fd);
	}
	return (ret);
}
