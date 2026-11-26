/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 13:26:47 by ymoubtas          #+#    #+#             */
/*   Updated: 2026/11/26 13:26:48 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

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
