#include "../push_swap.h"

static void	reverse_rotate(t_list **stack)
{
	t_list	*prev;
	t_list	*last;

	prev = *stack;
	while (prev && prev->next && prev->next->next)
		prev = prev->next;
	last = prev->next;
	prev->next = NULL;
	last->next = *stack;
	*stack = last;
}

void	rra(t_list **stack_a, t_count *count_ops)
{
	if (*stack_a == NULL || (*stack_a)->next == NULL)
		return ;
	reverse_rotate(stack_a);
	count_ops->rra++;
	printf("rra\n");
}

void	rrb(t_list **stack_b, t_count *count_ops)
{
	if (*stack_b == NULL || (*stack_b)->next == NULL)
		return ;
	reverse_rotate(stack_b);
	count_ops->rrb++;
	printf("rrb\n");
}
