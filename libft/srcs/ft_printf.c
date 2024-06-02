/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:12:04 by xcharra           #+#    #+#             */
/*   Updated: 2023/03/16 18:53:51 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	display(va_list args, char c)
{
	int		fd;

	fd = 1;
	if (c == 'c')
		return (ft_putchar(va_arg(args, int), fd));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *), fd));
	else if (c == 'p')
	{
		ft_putstr("0x", fd);
		return (2 + ft_putnbr_base(va_arg(args, size_t), HEXAL, fd));
	}
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int), fd));
	else if (c == 'u')
		return (ft_putunbr(va_arg(args, unsigned int), fd));
	else if (c == 'x')
		return (ft_putnbr_base(va_arg(args, unsigned int), HEXAL, fd));
	else if (c == 'X')
		return (ft_putnbr_base(va_arg(args, unsigned int), HEXAU, fd));
	else
		return (ft_putchar(c, fd));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	size_t	i;
	va_list	args;
	int		ret;
	int		fd;

	fd = 1;
	i = 0;
	va_start(args, str);
	ret = 0;
	if (write(1, 0, 0) < 0)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] != '%')
			ret += ft_putchar(str[i], fd);
		if (str[i] == '%' && str[i + 1])
		{
			ret += display(args, str[i + 1]);
			i++;
		}
		i++;
	}
	va_end(args);
	return (ret);
}
