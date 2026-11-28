/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:51:16 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 09:20:19 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	ft_conversion(int fd, va_list ap, char data_type)
{
	if (data_type == 'f')
		return (ft_print_float(fd, va_arg(ap, double)));
	if (data_type == 'd' || data_type == 'i')
		return (ft_printnbr_base(fd, va_arg(ap, int), "0123456789"));
	if (data_type == 's')
		return (ft_printstr(fd, va_arg(ap, char *)));
	if (data_type == '%')
		return (ft_printchar(fd, '%'));
	if (ft_printchar(fd, '%') < 0 || ft_printchar(fd, data_type) < 0)
		return (-1);
	return (2);
}

static int	ft_process(int fd, const char *f, va_list ap)
{
	int		written;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (f[i])
	{
		if (f[i] == '%' && f[i + 1] == '\0')
			return (-1);
		if (f[i] == '%')
			written = ft_conversion(fd, ap, f[++i]);
		else
			written = ft_printchar(fd, f[i]);
		if (written < 0)
			return (-1);
		count += written;
		i++;
	}
	return (count);
}

int	ft_dprintf(int fd, const char *f, ...)
{
	va_list	ap;
	int		count;

	if (!f || write(fd, 0, 0) < 0)
		return (-1);
	va_start(ap, f);
	count = ft_process(fd, f, ap);
	va_end(ap);
	return (count);
}
