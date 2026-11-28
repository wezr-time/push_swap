/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 09:57:48 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/28 08:29:53 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_list	*stack_a;
	t_flags	flags;
	int		i;

	i = 1;
	stack_a = NULL;
	flags = (t_flags){0};
	if (ac <= 1)
		return (0);
	ft_flags(ac, av, &flags, &i);
	ft_stack_fill(&stack_a, ac, av, i);
	ft_dup_nbr(&stack_a);
	ft_sort(&stack_a, &flags);
	ft_lstclear(&stack_a);
	return (0);
}
