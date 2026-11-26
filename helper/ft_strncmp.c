/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 14:56:51 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/21 09:51:25 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

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
