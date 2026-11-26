/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printaddress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 14:10:23 by ymoubtas          #+#    #+#             */
/*   Updated: 2026/11/26 11:20:22 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	ft_print(int fd, uintptr_t nbr, const char *src_base)
{
	int	written;
	int	count;

	count = 0;
	if (nbr >= 16)
	{
		written = ft_print(fd, nbr / 16, src_base);
		if (written < 0)
			return (-1);
		count += written;
	}
	written = ft_printchar(fd, src_base[nbr % 16]);
	if (written < 0)
		return (-1);
	count += written;
	return (count);
}

int	ft_printaddress(int fd, void *p)
{
	int	count;
	int	written;

	written = 0;
	if (p == 0)
		return (ft_printstr(fd, "(nil)"));
	if (ft_printstr(fd, "0x") < 0)
		return (-1);
	count = 2;
	written = ft_print(fd, (uintptr_t)p, "0123456789abcdef");
	if (written < 0)
		return (-1);
	count += written;
	return (count);
}
