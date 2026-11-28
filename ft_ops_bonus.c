/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ops_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 17:17:54 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 18:50:50 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	is_valid_op(char *s, char *op)
{
	if (ft_strlen(s) < ft_strlen(op))
		return (0);
	return (ft_strncmp(s, op, ft_strlen(s)) == 0);
}

int	ft_ops(t_list **a, t_list **b, char *s)
{
	if (is_valid_op(s, "pb\n"))
		pb_checker(a, b);
	else if (is_valid_op(s, "pa\n"))
		pa_checker(b, a);
	else if (is_valid_op(s, "sa\n"))
		sa_checker(*a);
	else if (is_valid_op(s, "sb\n"))
		sb_checker(*b);
	else if (is_valid_op(s, "ss\n"))
		ss_checker(*a, *b);
	else if (is_valid_op(s, "ra\n"))
		ra_checker(a);
	else if (is_valid_op(s, "rb\n"))
		rb_checker(b);
	else if (is_valid_op(s, "rr\n"))
		rr_checker(a, b);
	else if (is_valid_op(s, "rrb\n"))
		rrb_checker(b);
	else if (is_valid_op(s, "rra\n"))
		rra_checker(a);
	else if (is_valid_op(s, "rrr\n"))
		rrr_checker(a, b);
	else
		return (0);
	return (1);
}
