/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 14:11:02 by ymoubtas          #+#    #+#             */
/*   Updated: 2026/11/26 11:20:33 by mamehri          ###   ########.fr       */
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
