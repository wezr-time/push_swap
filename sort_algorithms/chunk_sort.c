/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 15:00:29 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 11:27:44 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	bring_to_top_a(t_list **a, size_t limit, size_t size, t_count *ops)
{
	size_t	pos;

	pos = in_range(*a, limit);
	if (pos < size - pos)
		while (pos--)
			ra(a, ops);
	else
	{
		pos = size - pos;
		while (pos--)
			rra(a, ops);
	}
}

static void	bring_to_top_b(t_list **b, size_t pos, size_t size, t_count *ops)
{
	if (pos < size - pos)
		while (pos--)
			rb(b, ops);
	else
	{
		pos = size - pos;
		while (pos--)
			rrb(b, ops);
	}
}

static void	phase_1(t_list **a, t_list **b, t_count *ops)
{
	size_t		size;
	int			offset;
	int			pushed;

	size = ft_lstsize(*a);
	offset = sqrt_of(size);
	pushed = 0;
	while (*a)
	{
		if ((*a)->index <= pushed + offset)
		{
			pb(a, b, ops);
			if ((*b)->index <= pushed)
				rb(b, ops);
			pushed++;
			size--;
		}
		else
			bring_to_top_a(a, pushed + offset + 1, size, ops);
	}
}

static void	phase_2(t_list **a, t_list **b, t_count *ops)
{
	size_t		size;
	size_t		pos;

	size = ft_lstsize(*b);
	while (*b)
	{
		pos = max_pos(*b);
		bring_to_top_b(b, pos, size, ops);
		pa(b, a, ops);
		size--;
	}
}

void	chunk_sort(t_list **a, t_list **b, t_count *ops)
{
	if (is_sort(*a))
		return ;
	phase_1(a, b, ops);
	phase_2(a, b, ops);
}
