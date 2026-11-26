/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 09:57:48 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 11:19:59 by mamehri          ###   ########.fr       */
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

// ft_dprintf(1, "\n================================\n");
// t_list	*curr = stack_a;
// while (curr)
// {
// 	ft_dprintf(1, "%d ", curr->content);
// 	curr = curr->next;
// }
// ft_dprintf(1, "\n================================\n");