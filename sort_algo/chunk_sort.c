#include "../push_swap.h"

static void	bring_to_top_a(t_list **stack_a, size_t limit, size_t size, t_count *count_ops)
{
	size_t	pos;

	pos = in_range(*stack_a, limit);
	if (pos < size - pos)
		while (pos--)
			ra(stack_a, count_ops);
	else
	{
		pos = size - pos;
		while (pos--)
			rra(stack_a, count_ops);
	}
}

static void	bring_to_top_b(t_list **stack_b, size_t pos, size_t size, t_count *count_ops)
{
	if (pos < size - pos)
		while (pos--)
			rb(stack_b, count_ops);
	else
	{
		pos = size - pos;
		while (pos--)
			rrb(stack_b, count_ops);
	}
}

static void	phase_1(t_list **stack_a, t_list **stack_b, t_count *count_ops)
{
	size_t		size;
	int			offset;
	int			pushed;

	size = ft_lstsize(*stack_a);
	offset = sqrt_of(size);
	pushed = 0;
	while (*stack_a)
	{
		if ((*stack_a)->index <= pushed + offset)
		{
			// 2n --> n
			pb(stack_a, stack_b, count_ops); // n
			if ((*stack_b)->index <= pushed)
				rb(stack_b, count_ops); // n
			pushed++;
			size--;
		}
		else
			bring_to_top_a(stack_a, pushed + offset + 1, size, count_ops);
	}
}

static void	phase_2(t_list **stack_a, t_list **stack_b, t_count *count_ops)
{
	size_t		size;
	size_t		pos;

	size = ft_lstsize(*stack_b);
	while (*stack_b)
	{
		pos = max_of(*stack_b);
		bring_to_top_b(stack_b, pos, size, count_ops);
		pa(stack_b, stack_a, count_ops);
		size--;
	}
}

void	chunk_sort(t_list **stack_a, t_list **stack_b, t_count *count_ops)
{
	if (is_sort(*stack_a))
		return ;
	phase_1(stack_a, stack_b, count_ops);
	phase_2(stack_a, stack_b, count_ops);
}
