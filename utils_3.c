/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 14:58:14 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 10:15:37 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		write(fd, s + i, 1);
		i++;
	}
	return (1);
}

static int	ft_convert_to_nbr(const char *nptr, int sign, int *check)
{
	size_t	i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + nptr[i] - '0';
		if ((nbr * sign > INT_MAX) || (nbr * sign < INT_MIN))
		{
			*check = 0;
			return (-1);
		}
		i++;
	}
	if (nptr[i])
	{
		*check = 0;
		return (-1);
	}
	return (nbr * sign);
}

int	ft_atoi(const char *nptr, int *check)
{
	size_t	i;
	int		sign;

	if (!*nptr)
		return (0);
	i = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	if (!nptr[i])
	{
		*check = 0;
		return (-1);
	}
	return (ft_convert_to_nbr(nptr + i, sign, check));
}
