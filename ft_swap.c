/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:55:43 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 16:43:24 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_list *lst)
{
	int	content;
	int	index;

	if (!lst)
		return ;
	content = lst->content;
	index = lst->index;
	lst->content = lst->next->content;
	lst->index = lst->next->index;
	lst->next->content = content;
	lst->next->index = index;
}

void	sa(t_list *a, t_count *ops)
{
	swap(a);
	ft_dprintf(1, "sa\n");
	ops->sa++;
}

void	sb(t_list *b, t_count *ops)
{
	swap(b);
	ft_dprintf(1, "sb\n");
	ops->sb++;
}

void	ss(t_list *a, t_list *b, t_count *ops)
{
	sa(a, ops);
	sb(b, ops);
}
