/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:28:06 by xcharra           #+#    #+#             */
/*   Updated: 2023/04/28 16:45:31 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(double n, long num, size_t len, size_t precision)
{
	if (num == 0)
		len = 1;
	while (num != 0)
	{
		len++;
		num /= 10;
	}
	len += precision + 1;
	if (n < 0)
		len++;
	return (len);
}

static size_t	get_int_part(char *str, double n, long num, size_t i)
{
	long	tmp;
	size_t	ret;

	ret = i;
	num = (long)n;
	tmp = num;
	while (tmp)
	{
		tmp /= 10;
		ret++;
	}
	while (num)
	{
		str[ret - 1] = (num % 10) + '0';
		num /= 10;
		ret--;
		i++;
	}
	if (n < 1 && n > -1)
		str[i++] = '0';
	return (i - 1);
}

static void	get_dec_part(char *str, double dec, long num, size_t len)
{
	size_t	i;

	i = 0;
	str[i] = '.';
	i++;
	while (i < len)
	{
		dec *= 10;
		num = (long)dec;
		str[i] = (num % 10) + '0';
		dec -= (double)num;
		i++;
	}
	str[i] = '\0';
}

char	*ft_dtoa(double n, size_t precision)
{
	char	*str;
	size_t	i;
	size_t	len;
	double	dec;
	long	num;

	len = 0;
	num = (long)n;
	len = get_len(n, num, len, precision);
	str = malloc(sizeof(char) * (len + 2));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[i++] = '-';
		n = -n;
	}
	i = get_int_part(str, n, num, i);
	dec = n - (double)num;
	len -= i;
	get_dec_part(&str[i + 1], dec, num, len);
	return (str);
}
