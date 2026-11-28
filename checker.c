/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 14:27:08 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/28 08:19:58 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	ft_read_ops(t_list **a, t_ops_list **op)
{
	t_ops_list	*node;
	char		*s;

	while (1)
	{
		s = get_next_line(0);
		if (!s)
			break ;
		node = bonus_lstnew(s);
		if (!node)
		{
			ft_lstclear(a);
			bonus_lstclear(op);
			get_next_line(-1);
			exit (ft_putstr_fd("Error\n", 2));
		}
		bonus_lstadd_back(op, node);
	}
}

static void	ft_apply_ops(t_list **a, t_list **b, t_ops_list **op)
{
	t_ops_list	*node;
	int			check;

	node = *op;
	while (node)
	{
		check = ft_ops(a, b, node->op);
		if (!check)
		{
			ft_lstclear(a);
			ft_lstclear(b);
			bonus_lstclear(op);
			exit (ft_putstr_fd("Error\n", 2));
		}
		node = node->next;
	}
	bonus_lstclear(op);
}

static void	checker(t_list **a, t_list **b)
{
	t_ops_list	*op;

	op = NULL;
	ft_read_ops(a, &op);
	ft_apply_ops(a, b, &op);
	if (*b == NULL && is_sort(*a))
		ft_dprintf(1, "OK\n");
	else
		ft_dprintf(1, "KO\n");
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	int		i;

	i = 1;
	a = NULL;
	b = NULL;
	if (argc <= 1)
		return (0);
	ft_stack_fill(&a, argc, argv, i);
	ft_dup_nbr(&a);
	checker(&a, &b);
	ft_lstclear(&a);
}
