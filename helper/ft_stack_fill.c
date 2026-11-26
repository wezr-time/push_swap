/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 17:31:36 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 10:01:23 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	ft_free(char **splitted)
{
	size_t	i;

	i = 0;
	while (splitted[i] != NULL)
		free(splitted[i++]);
	free(splitted);
}

static void	ft_exit(t_list **lst, char **s)
{
	ft_free(s);
	ft_lstclear(lst);
	exit (ft_putstr_fd("Error\n", 2));
}

static void	ft_fill(t_list **stack_a, char **splitted)
{
	t_list	*new_node;
	int		check;
	int		nbr;
	int		j;

	j = 0;
	check = 1;
	new_node = NULL;
	while (splitted[j] != NULL)
	{
		nbr = ft_atoi(splitted[j], &check);
		if (!check)
			ft_exit(stack_a, splitted);
		new_node = ft_lstnew(nbr);
		if (!new_node)
			ft_exit(stack_a, splitted);
		ft_lstadd_back(stack_a, new_node);
		j++;
	}
}

void	ft_stack_fill(t_list **stack_a, int ac, char **av, int i)
{
	char	**splitted;

	while (i < ac)
	{
		splitted = ft_split(av[i++], ' ');
		if (!splitted)
		{
			ft_lstclear(stack_a);
			exit(ft_putstr_fd("Error\n", 2));
		}
		ft_fill(stack_a, splitted);
		ft_free(splitted);
	}
	ft_set_index(*stack_a);
}
