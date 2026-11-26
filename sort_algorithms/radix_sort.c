/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 14:44:49 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 11:28:10 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_bits(t_list *a)
{
	int	max;
	int	bits;

	bits = 0;
	max = a->index;
	while (a)
	{
		if (a->index > max)
			max = a->index;
		a = a->next;
	}
	while (max >> bits)
		bits++;
	return (bits);
}

void	radix_sort(t_list **a, t_list **b, t_count *ops)
{
	int		size_a;
	int		bits;
	int		bit;

	bit = 0;
	bits = ft_bits(*a);
	while (bit < bits)
	{
		size_a = ft_lstsize(*a);
		while (size_a--)
		{
			if (((*a)->index >> bit) & 1)
				ra(a, ops);
			else
				pb(a, b, ops);
		}
		while ((*b))
			pa(b, a, ops);
		bit++;
	}
}
