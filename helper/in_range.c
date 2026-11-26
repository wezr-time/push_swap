/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:26:39 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 11:26:40 by mamehri          ###   ########.fr       */
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
