/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:26:39 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 11:23:24 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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
