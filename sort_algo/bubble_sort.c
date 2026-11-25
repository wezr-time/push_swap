#include "../push_swap.h"

// pa pb rra ra

int	smallest(t_list	*stack_a)
{
	t_list	*curr;
	int 	val;
	int		pos;

	curr = stack_a;
	val = curr->nbr;
	while (curr )
	{
		if (curr->nbr < val)
			val = curr->nbr;
		curr = curr->next;
	}
	curr = stack_a;
	pos = 0;
	while (curr && curr->nbr != val)
	{
		pos++;
		curr = curr->next;
	}
	return (pos);
}





int	is_sort(t_list *stack_a)
{
	t_list	*curr;

	curr = stack_a;
	while (curr && curr->next)
	{
		if (curr->nbr > curr->next->nbr)
			return (0);
		curr = curr->next;
	}
	return (1);
}

void	bubble_sort(t_list **stack_a)
{
	t_list			*stack_b;
	unsigned int	pos_min;
	unsigned int	size;

	stack_b = NULL;
	while (1)
	{
		size = ft_lstsize(*stack_a);
		while (*stack_a && (*stack_a)->next)
		{
			pos_min = smallest(*stack_a);
			if (pos_min < size - pos_min)
				while (pos_min--)
					ra(stack_a);
			else
			{
				pos_min = size - pos_min;
				while (pos_min--)
					rra(stack_a);
			}
			size--;
			pb(stack_a, &stack_b);
		}
		while (stack_b)
			pa(&stack_b, stack_a);		
		if (is_sort(*stack_a) == 1)
			return ;
	}
}