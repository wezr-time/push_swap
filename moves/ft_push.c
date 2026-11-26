/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 13:27:07 by ymoubtas          #+#    #+#             */
/*   Updated: 2026/11/26 13:27:08 by ymoubtas         ###   ########.fr       */
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
