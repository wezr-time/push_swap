/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverce_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 13:27:11 by ymoubtas          #+#    #+#             */
/*   Updated: 2026/11/26 13:27:12 by ymoubtas         ###   ########.fr       */
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
