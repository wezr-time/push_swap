#include "../push_swap.h"

size_t	in_range(t_list *stack_a, int range)
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