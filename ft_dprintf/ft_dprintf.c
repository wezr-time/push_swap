/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 14:10:48 by ymoubtas          #+#    #+#             */
/*   Updated: 2026/11/26 11:33:17 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	ft_conversion(int fd, va_list ap, char data_type)
{
	char	*base[3];

	base[0] = "0123456789";
	base[1] = "0123456789abcdef";
	base[2] = "0123456789ABCDEF";
	if (data_type == 'd' || data_type == 'i')
		return (ft_printnbr_base(fd, va_arg(ap, int), base[0]));
	if (data_type == 'u')
		return (ft_printnbr_base(fd, va_arg(ap, unsigned int), base[0]));
	if (data_type == 'x')
		return (ft_printnbr_base(fd, va_arg(ap, unsigned int), base[1]));
	if (data_type == 'X')
		return (ft_printnbr_base(fd, va_arg(ap, unsigned int), base[2]));
	if (data_type == 'c')
		return (ft_printchar(fd, va_arg(ap, int)));
	if (data_type == 's')
		return (ft_printstr(fd, va_arg(ap, char *)));
	if (data_type == 'p')
		return (ft_printaddress(fd, va_arg(ap, void *)));
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
