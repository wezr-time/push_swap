#include "push_swap.h"

size_t	get_max_bits(int max_index)
{
	size_t	bits;

	bits = 0;
	while ((max_index >> bits) != 0)
		bits++;
	return (bits);
}

int	max_index(t_list *list)
{
	int	big;

	big = list->index;
	while (list)
	{
		if (list->index > big)
			big = list->index;
		list = list->next;
	}
	return (big);
}

void	radix_sort(t_list **stack_a)
{
	t_list	*stack_b;
	size_t	max_bits;
	size_t	bit;
	size_t	size;

	stack_b = NULL;
	max_bits = get_max_bits(max_index(*stack_a));
	bit = 0;
	while (bit < max_bits)
	{
		size = ft_lstsize(*stack_a);
		while (size--)
		{
			if (((*stack_a)->index >> bit) & 1)
				r_ab(stack_a, "ra");
			else
				*stack_a = push(*stack_a, &stack_b, "pb");
		}
		while (stack_b)
			stack_b = push(stack_b, stack_a, "pa");
		bit++;		
	}
}
