/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 10:12:38 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 11:18:11 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	ft_total(t_count *c)
{
	return (c->pa + c->pb + c->ra + c->rb + c->rrb + c->sa + c->sb + c->rra);
}

static void	ft_bench(t_flags *flags_list, t_count *ops)
{
	ft_dprintf(2, "[bench] disorder:	%f\n", ops->disorder);
	ft_dprintf(2, "[bench] strategy:	");
	if (flags_list->adaptive)
		ft_dprintf(2, "Adaptive / ");
	else if (flags_list->simple)
		ft_dprintf(2, "Simple / ");
	else if (flags_list->medium)
		ft_dprintf(2, "Medium / ");
	else if (flags_list->complex)
		ft_dprintf(2, "Complex / ");
	if (flags_list->simple)
		ft_dprintf(2, "O(n²)\n");
	else if (flags_list->medium)
		ft_dprintf(2, "O(n√n)\n");
	else if (flags_list->complex)
		ft_dprintf(2, "O(n log n)\n");
	ft_dprintf(2, "[bench] total_ops:	%d\n", ft_total(ops));
	ft_dprintf(2, "[bench] sa:	%d	sb:	%d	ss:	0	pa:	%d	pb:	%d\n",
		ops->sa, ops->sb, ops->pa, ops->pb);
	ft_dprintf(2, "[bench] ra:	%d	rb:	%d	rr:	0\
	rra:	%d	rrb:	%d	rrr:	0\n",
		ops->ra, ops->rb, ops->rra, ops->rrb);
}

static float	ft_disorder(t_list *a)
{
	t_list	*curr;
	int		mistakes;
	int		total_pairs;

	mistakes = 0;
	total_pairs = 0;
	while (a)
	{
		curr = a->next;
		while (curr)
		{
			total_pairs += 1;
			if (a->content > curr->content)
				mistakes++;
			curr = curr->next;
		}
		a = a->next;
	}
	return ((float)mistakes / total_pairs);
}

static void	adapt_algo(t_list **a, t_list **b, t_count *ops, t_flags *flags)
{
	if (ops->disorder < 0.2)
	{
		flags->simple = 1;
		selection_sort(a, b, ops);
	}
	else if (ops->disorder < 0.5)
	{
		flags->medium = 1;
		chunk_sort(a, b, ops);
	}
	else
	{
		flags->complex = 1;
		radix_sort(a, b, ops);
	}
}

void	ft_sort(t_list **a, t_flags *flags)
{
	t_list	*b;
	t_count	ops;

	b = NULL;
	ops = (t_count){0};
	ops.disorder = ft_disorder(*a);
	if (flags->simple || flags->medium || flags->complex)
		flags->adaptive = 0;
	if (flags->simple)
		selection_sort(a, &b, &ops);
	else if (flags->medium)
		chunk_sort(a, &b, &ops);
	else if (flags->complex)
		radix_sort(a, &b, &ops);
	else
		adapt_algo(a, &b, &ops, flags);
	if (flags->bench)
		ft_bench(flags, &ops);
}
