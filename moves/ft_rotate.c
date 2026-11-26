/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 13:27:17 by ymoubtas          #+#    #+#             */
/*   Updated: 2026/11/26 13:27:18 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rotate(t_list **stack)
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

void	ra(t_list **stack_a, t_count *count_ops)
{
	if (!(*stack_a) || !(*stack_a)->next)
		return ;
	rotate(stack_a);
	count_ops->ra++;
	ft_dprintf(1, "ra\n");
}

void	rb(t_list **stack_b, t_count *count_ops)
{
	if (!(*stack_b) || !(*stack_b)->next)
		return ;
	rotate(stack_b);
	count_ops->rb++;
	ft_dprintf(1, "rb\n");
}
