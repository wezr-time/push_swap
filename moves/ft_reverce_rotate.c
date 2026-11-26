/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverce_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:47:58 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 11:18:37 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	reverse_rotate(t_list **stack)
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

void	rra(t_list **stack_a, t_count *count_ops)
{
	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
	reverse_rotate(stack_a);
	count_ops->rra++;
	ft_dprintf(1, "rra\n");
}

void	rrb(t_list **stack_b, t_count *count_ops)
{
	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return ;
	reverse_rotate(stack_b);
	count_ops->rrb++;
	ft_dprintf(1, "rrb\n");
}
