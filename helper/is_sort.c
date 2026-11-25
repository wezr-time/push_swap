#include "../push_swap.h"

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