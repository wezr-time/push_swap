/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverce_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:47:58 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 11:14:34 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

void	rra_checker(t_list **a)
{
	if (*a == NULL || (*a)->next == NULL)
		return ;
	reverse_rotate(a);
}

void	rrb_checker(t_list **b)
{
	if (*b == NULL || (*b)->next == NULL)
		return ;
	reverse_rotate(b);
}

void	rrr_checker(t_list **a, t_list **b)
{
	rra_checker(a);
	rrb_checker(b);
}
