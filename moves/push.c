#include "../push_swap.h"

static void	push(t_list **from, t_list **to)
{
	t_list	*curr_a;

	if (*from == NULL)
		return ;
	curr_a = (*from)->next;
	(*from)->next = *to;
	*to = *from;
	*from = curr_a;
}

void	pb(t_list **stack_a, t_list **stack_b, t_count *count_ops)
{
	count_ops->pa++;
	push(stack_a, stack_b);
	printf("pb\n");
}

void	pa(t_list **stack_b, t_list **stack_a, t_count *count_ops)
{
	count_ops->pb++;
	push(stack_b, stack_a);
	printf("pa\n");
}
