#include "../push_swap.h"

// pa pb ra rb rrb

size_t	sqrt_of(size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 1;
	while (i < n / i)
		i++;
	return (i);
}

static size_t	in_range(t_list *stack_a, int range)
{
	size_t	pos;

	pos = 0;
	while (stack_a && stack_a->index >= range)
	{
		stack_a = stack_a->next;
		pos++;
	}
	return (pos);
}

size_t	max_of(t_list *stack_b)
{
	t_list	*curr;
	size_t	pos;
	int		val;

	curr = stack_b;
	val = curr->nbr;
	while (curr)
	{
		if (curr->nbr > val)
			val = curr->nbr;
		curr = curr->next;
	}
	curr = stack_b;
	pos = 0;
	while (curr && curr->nbr != val)
	{
		pos++;
		curr = curr->next;
	}
	return (pos);
}

void	bring_to_top_a(t_list **stack_a, size_t pos, size_t size)
{
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

void	bring_to_top_b(t_list **stack_b, size_t pos, size_t size)
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

void	phase_1(t_list **stack_a, t_list **stack_b)
{
	size_t		n_chunks;
	size_t		size;
	size_t		pos;
	int			chunk;
	int		pushed;
	int		limit;

	size = ft_lstsize(*stack_a);
	if (size == 0)
		return ;
	n_chunks = sqrt_of(size);
	chunk = size / n_chunks;
	limit = chunk;
	pushed = 0;
	while (*stack_a)
	{
		if (pushed == limit)
			limit += chunk;
		pos = in_range(*stack_a, limit);
		if ((*stack_a)->index < limit)
		{
			pb(stack_a, stack_b);
			pushed++;
			size--;
		}
		else
			bring_to_top_a(stack_a, pos, size);
	}
}

void	phase_2(t_list **stack_a, t_list **stack_b)
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
