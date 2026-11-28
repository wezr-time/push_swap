/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:26:39 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 10:10:47 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	in_range(t_list *a, int range)
{
	size_t	pos;

	pos = 0;
	while (a && a->index >= range)
	{
		a = a->next;
		pos++;
	}
	return (pos);
}

int	is_sort(t_list *head)
{
	while (head && head->next)
	{
		if (head->content > head->next->content)
			return (0);
		head = head->next;
	}
	return (1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (i < n)
	{
		res = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (res != 0)
			break ;
		if (!s1[i] || !s2[i])
			break ;
		i++;
	}
	return (res);
}

size_t	ft_strlen(const	char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	sqrt_of(long n)
{
	long	i;

	i = 1;
	if (n == 0)
		return (0);
	while (i <= n / i)
		i++;
	return (i);
}
