/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:55:56 by ymoubtas          #+#    #+#             */
/*   Updated: 2026/11/26 11:55:57 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

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
