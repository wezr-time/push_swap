/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverce_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:47:58 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 16:42:05 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_rotate(t_list **stack)
{
	t_list	*prev;
	t_list	*last;

	prev = *stack;
	while (prev && prev->next && prev->next->next)
		prev = prev->next;
	last = prev->next;
	prev->next = NULL;
	last->next = *stack;
	*stack = last;
}

void	rra(t_list **a, t_count *ops)
{
	if (*a == NULL || (*a)->next == NULL)
		return ;
	reverse_rotate(a);
	ops->rra++;
	ft_dprintf(1, "rra\n");
}

void	rrb(t_list **b, t_count *ops)
{
	if (*b == NULL || (*b)->next == NULL)
		return ;
	reverse_rotate(b);
	ops->rrb++;
	ft_dprintf(1, "rrb\n");
}

void	rrr(t_list **a, t_list **b, t_count *ops)
{
	rra(a, ops);
	rrb(b, ops);
}
