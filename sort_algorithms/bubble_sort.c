/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 15:00:19 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 11:08:34 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	bubble_sort(t_list **a, t_list **b, t_count *ops)
{
	while (is_sort(*a) != 1)
	{
		while (*a && (*a)->next)
		{
			if ((*a)->content > (*a)->next->content)
				sa(*a, ops);
			pb(a, b, ops);
		}
		while (*b)
		{
			if ((*b)->next && (*b)->content < (*b)->next->content)
				sb(*b, ops);
			pa(b, a, ops);
		}
	}
}

static int	smallest_index(t_list	*a)
{
	t_list	*curr;
	int		val;
	int		pos;

	curr = a;
	val = curr->content;
	while (curr)
	{
		if (curr->content < val)
			val = curr->content;
		curr = curr->next;
	}
	curr = a;
	pos = 0;
	while (curr && curr->content != val)
	{
		pos++;
		curr = curr->next;
	}
	return (pos);
}

void	selection_sort(t_list **a, t_list **b, t_count *ops)
{
	unsigned int	pos_min;
	unsigned int	size;

	while (is_sort(*a) != 1)
	{
		size = ft_lstsize(*a);
		while ((*a)->next)
		{
			pos_min = smallest_index(*a);
			if (pos_min < size - pos_min)
				while (pos_min--)
					ra(a, ops);
			else
			{
				pos_min = size - pos_min;
				while (pos_min--)
					rra(a, ops);
			}
			size--;
			pb(a, b, ops);
		}
		while (*b)
			pa(b, a, ops);
	}
}
