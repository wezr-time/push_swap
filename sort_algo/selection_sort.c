#include "../push_swap.h"

static int	smallest_index(t_list	*stack_a)
{
	t_list	*curr;
	int		val;
	int		pos;

	curr = stack_a;
	val = curr->nbr;
	while (curr)
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

void	selection_sort(t_list **stack_a, t_list **stack_b)
{
	unsigned int	pos_min;
	unsigned int	size;

	while (is_sort(*stack_a) != 1)
	{
		size = ft_lstsize(*stack_a);
		while (*stack_a && (*stack_a)->next)
		{
			pos_min = smallest_index(*stack_a);
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
			pb(stack_a, stack_b);
		}
		while (*stack_b)
			pa(stack_b, stack_a);
	}
}
