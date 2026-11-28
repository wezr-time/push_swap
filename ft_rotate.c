/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:47:29 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 16:42:25 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_list **stack)
{
	t_list	*first;
	t_list	*last;

	first = (*stack);
	last = first;
	while (last && last->next)
		last = last->next;
	last->next = first;
	(*stack) = first->next;
	first->next = NULL;
}

void	ra(t_list **a, t_count *ops)
{
	if (!(*a) || !(*a)->next)
		return ;
	rotate(a);
	ops->ra++;
	ft_dprintf(1, "ra\n");
}

void	rb(t_list **b, t_count *ops)
{
	if (!(*b) || !(*b)->next)
		return ;
	rotate(b);
	ops->rb++;
	ft_dprintf(1, "rb\n");
}

void	rr(t_list **a, t_list **b, t_count *ops)
{
	ra(a, ops);
	rb(b, ops);
}
