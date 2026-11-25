#include "../push_swap.h"

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
