/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:47:29 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 11:14:29 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

void	ra_checker(t_list **a)
{
	if (!(*a) || !(*a)->next)
		return ;
	rotate(a);
}

void	rb_checker(t_list **b)
{
	if (!(*b) || !(*b)->next)
		return ;
	rotate(b);
}

void	rr_checker(t_list **a, t_list **b)
{
	ra_checker(a);
	rb_checker(b);
}
