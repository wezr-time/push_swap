#include "push_swap.h"

static int	sqrt_of(int n)
{
	int	i;

	i = 0;
	while (i * i <= n)
		i++;
	return (i);
}

static int	max_of(t_list *list)
{
	t_list	*curr;
	int		value;
	int		pos;

	curr = list;
	value = list->content;
	while (curr)
	{
		if (curr->content > value)
			value = curr->content;
		curr = curr->next;
	}
	pos = 0;
	while (list && list->content != value)
	{
		pos++;
		list = list->next;
	}
	return (pos);
}

static void	move_to_stack_b(t_list **stack_a, t_list **stack_b)
{
	int		limit;
	int		pushed;
	int		size;
	int		chunks;

	size = ft_lstsize(*stack_a);
	chunks = sqrt_of(size);
	pushed = 0;
	limit = size / chunks;
	while (*stack_a)
	{
		if ((*stack_a)->index < limit)
		{
			*stack_a = push((*stack_a), stack_b, "pb");
			pushed++;
			if (pushed == limit)
				limit += size / chunks;
		}
		else
			r_ab(stack_a, "ra");
	}
}

static void	move_to_stack_a(t_list **stack_a, t_list **stack_b)
{
	size_t	pos;
	size_t	size_b;

	while (*stack_b)
	{
		pos = max_of(*stack_b);
		size_b = ft_lstsize(*stack_b);
		if (pos < size_b - pos)
			while (pos--)
				r_ab(stack_b, "rb");
		else
		{
			pos = size_b - pos;
			while (pos--)
				rr_ab(stack_b, "rrb");
		}
		*stack_b = push(*stack_b, stack_a, "pa");
	}
}

void	chunk_sort(t_list **stack_a)
{
	t_list	*stack_b;

	stack_b = NULL;
	move_to_stack_b(stack_a, &stack_b);
	move_to_stack_a(stack_a, &stack_b);
}
