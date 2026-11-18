#include "push_swap.h"

int	is_sort(t_list *head)
{
	while (head && head->next)
	{
		if (head->content > head->next->content)
			return (0);
		head = head->next;
	}
	return (1);
}

void	bubble_sort(t_list **stack_a)
{
	t_list	*stack_b;

	stack_b = NULL;
	while (is_sort(*stack_a) != 1)
	{
		while (*stack_a && (*stack_a)->next)
		{
			if ((*stack_a)->content > (*stack_a)->next->content)
				swap((*stack_a), (*stack_a)->next, "sa");
			*stack_a = push((*stack_a), &stack_b, "pb");
		}
		while (stack_b)
		{
			if (stack_b->next && stack_b->content < stack_b->next->content)
				swap((stack_b), stack_b->next, "sb");
			stack_b = push(stack_b, stack_a, "pa");
		}
	}
}
