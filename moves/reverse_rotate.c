#include "../push_swap.h"

static void	reverse_rotate(t_list **stack)
{
	t_list	*prev;
	t_list	*last;

	if (*stack == NULL || (*stack)->next == NULL)
		return ;
	prev = *stack;
	while (prev && prev->next && prev->next->next)
		prev = prev->next;
	last = prev->next;
	prev->next = NULL;
	last->next = *stack;
	*stack = last;
}

void	rra(t_list **stack_a)
{
	reverse_rotate(stack_a);
	printf("rra\n");
}

void	rrb(t_list **stack_b)
{
	reverse_rotate(stack_b);
	printf("rrb\n");
}
