/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_custom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:54:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/18 17:45:29 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	verif_arg_exit(char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
	{
		if (nbr[i] == '-' || nbr[i] == '+')
			i++;
		if (!ft_isdigit(nbr[i]))
		{
			g_exit_status = 2;
			return (0);
		}
		i++;
	}
	return (1);
}

bool	real_atoi(const char *nbr, int *nb_ret)
{
	int				i;
	int				m;
	long long int	nb;

	nb = 0;
	m = 1;
	i = 0;
	while (nbr[i] == 32 || (nbr[i] >= 9 && nbr[i] <= 13))
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			m *= -1;
		i++;
	}
	while (nbr[i] && (nbr[i] >= '0' && nbr[i] <= '9'))
	{
		if (nb != ((nb * 10 + (m * (nbr[i] - 48))) / 10))
			return (false);
		nb = nb * 10;
		nb = nb + (nbr[i] - '0') * m;
		i++;
	}
	*nb_ret = (int)nb;
	return (true);
}

/**
 * @brief A custom ft_atoi the print error when exit number is not right or
 * contains non-digit char
 * @param nbr
 * @param nb_ret
 * @return False if there's an error, True otherwise
 */
bool	ft_atoi_custom(const char *nbr, unsigned int *nb_ret)
{
	if (!(verif_arg_exit((char *)nbr)))
	{
		ft_fdprintf(1, "exit\n");
		ft_fdprintf(2, MSH E_EXIT"%s"NUM_ARG, nbr);
		return (false);
	}
	if (!real_atoi(nbr, (int *)nb_ret))
	{
		ft_fdprintf(1, "exit\n");
		ft_fdprintf(2, MSH E_EXIT"%s"NUM_ARG, nbr);
		return (false);
	}
	return (true);
}
