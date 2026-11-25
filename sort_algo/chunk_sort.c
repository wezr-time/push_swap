#include "../push_swap.h"

// pa pb ra rb rrb
static void	bring_to_top_a(t_list **stack_a, size_t limit, size_t size)
{
	size_t	pos;

	pos = in_range(*stack_a, limit);
	if (pos < size - pos)
		while (pos--)
			ra(stack_a);
	else
	{
		pos = size - pos;
		while (pos--)
			rra(stack_a);
	}
}

static void	bring_to_top_b(t_list **stack_b, size_t pos, size_t size)
{
	if (pos < size - pos)
		while (pos--)
			rb(stack_b);
	else
	{
		pos = size - pos;
		while (pos--)
			rrb(stack_b);
	}
}

static void	phase_1(t_list **stack_a, t_list **stack_b)
{
	size_t		n_chunks;
	size_t		size;
	int			chunk;
	int			pushed;
	int			limit;

	size = ft_lstsize(*stack_a);
	n_chunks = sqrt_of(size);
	chunk = size / n_chunks;
	limit = chunk;
	pushed = 0;
	while (*stack_a)
	{
		if (pushed == limit)
			limit += chunk;
		if ((*stack_a)->index < limit)
		{
			pb(stack_a, stack_b);
			pushed++;
			size--;
		}
		else
			bring_to_top_a(stack_a, limit, size);
	}
}

static void	phase_2(t_list **stack_a, t_list **stack_b)
{
	size_t		size;
	size_t		pos;

	size = ft_lstsize(*stack_b);
	while (*stack_b)
	{
		pos = max_of(*stack_b);
		bring_to_top_b(stack_b, pos, size);
		pa(stack_b, stack_a);
		size--;
	}
}

void	chunk_sort(t_list **stack_a)
{
	t_list		*stack_b;

	stack_b = NULL;
	phase_1(stack_a, &stack_b);
	phase_2(stack_a, &stack_b);
}
