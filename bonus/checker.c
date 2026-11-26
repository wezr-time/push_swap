/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 14:27:08 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/23 13:48:06 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	ft_operation(t_list **stack_a, t_list **stack_b, char *s)
{
	if (!ft_strncmp(s, "pb", 2))
		*stack_a = psh(*stack_a, stack_b);
	else if (!ft_strncmp(s, "pa", 2))
		*stack_b = psh(*stack_b, stack_a);
	else if (!ft_strncmp(s, "sa", 2))
		sp(*stack_a, (*stack_a)->next);
	else if (!ft_strncmp(s, "sb", 2))
		sp(*stack_b, (*stack_b)->next);
	else if (!ft_strncmp(s, "ra", 2))
		rab(stack_a);
	else if (!ft_strncmp(s, "rb", 2))
		rab(stack_b);
	else if (!ft_strncmp(s, "rrb", 3))
		rrab(stack_b);
	else if (!ft_strncmp(s, "rra", 3))
		rrab(stack_a);
	else
	{
		ft_lstclear(stack_a);
		ft_lstclear(stack_b);
		exit(ft_putstr_fd("Error\n", 2));
	}
}

static void	checker(t_list **stack_a)
{
	t_list	*stack_b;
	char	*s;

	stack_b = NULL;
	s = get_next_line(0);
	while (s != NULL)
	{
		ft_operation(stack_a, &stack_b, s);
		free(s);
		s = get_next_line(0);
	}
	if (stack_b == NULL && is_sort(*stack_a) == 1)
		ft_printf(1, "OK\n");
	else
		ft_printf(1, "KO\n");
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	int		i;

	if (argc <= 1)
		return (0);
	i = 1;
	stack_a = NULL;
	ft_stack_fill(&stack_a, argc, argv, i);
	checker(&stack_a);
	ft_lstclear(&stack_a);
}
