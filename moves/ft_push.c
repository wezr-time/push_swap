/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:46:05 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 11:18:34 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	push(t_list **from, t_list **to)
{
	t_list	*curr_a;

	curr_a = (*from)->next;
	(*from)->next = *to;
	*to = *from;
	*from = curr_a;
}

void	pb(t_list **stack_a, t_list **stack_b, t_count *count_ops)
{
	if (*stack_a == NULL)
		return ;
	count_ops->pb++;
	push(stack_a, stack_b);
	ft_dprintf(1, "pb\n");
}

void	pa(t_list **stack_b, t_list **stack_a, t_count *count_ops)
{
	if (*stack_b == NULL)
		return ;
	count_ops->pa++;
	push(stack_b, stack_a);
	ft_dprintf(1, "pa\n");
}
