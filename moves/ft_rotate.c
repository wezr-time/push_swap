/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:47:29 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 11:28:33 by mamehri          ###   ########.fr       */
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
