/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:52:32 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 10:17:33 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	ft_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_printnbr_base(int fd, long n, char *srcbase)
{
	int	count;
	int	written;
	int	base;

	count = 0;
	written = 0;
	base = ft_len(srcbase);
	if (n < 0)
	{
		if (ft_printchar(fd, '-') < 0)
			return (-1);
		count++;
		n = -n;
	}
	if (n >= base)
	{
		written = ft_printnbr_base(fd, n / base, srcbase);
		if (written < 0)
			return (-1);
		count += written;
	}
	written = ft_printchar(fd, srcbase[n % base]);
	if (written < 0)
		return (-1);
	return (count + written);
}

int	ft_print_float(int fd, double nbr_float)
{
	int	pct;
	int	count;
	int	written;

	pct = nbr_float * 10000;
	count = ft_printnbr_base(fd, pct / 100, "0123456789");
	if (count < 0 || ft_printchar(fd, '.') < 0)
		return (-1);
	if (pct % 100 < 10)
	{
		if (ft_printchar(fd, '0') < 0)
			return (-1);
		count++;
	}
	count++;
	written = ft_printnbr_base(fd, pct % 100, "0123456789");
	if (written < 0)
		return (-1);
	count += written;
	if (ft_printchar(fd, '%') < 0)
		return (-1);
	return (count + 1);
}

int	ft_printstr(int fd, char *s)
{
	int	count;

	if (!s)
		return (ft_printstr(fd, "(null)"));
	count = 0;
	while (s[count])
	{
		if (ft_printchar(fd, s[count]) < 0)
			return (-1);
		count++;
	}
	return (count);
}

int	ft_printchar(int fd, int c)
{
	return (write(fd, &c, 1));
}
