/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:46:05 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 11:11:26 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	push(t_list **from, t_list **to)
{
	t_list	*curr_a;

	curr_a = (*from)->next;
	(*from)->next = *to;
	*to = *from;
	*from = curr_a;
}

void	pb_checker(t_list **a, t_list **b)
{
	if (*a == NULL)
		return ;
	push(a, b);
}

void	pa_checker(t_list **b, t_list **a)
{
	if (*b == NULL)
		return ;
	push(b, a);
}
