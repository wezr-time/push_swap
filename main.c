#include "push_swap.h"
#include <stdio.h>

void	r_ab(t_list **head, char *s)
{
	t_list	*first;

	first = *head;
	*head = (*head)->next;
	while (*head && (*head)->next)
		head = &(*head)->next;
	(*head)->next = first;
	printf("%s\n", s);
}

void	rr_ab(t_list **head, char *s)
{
	t_list	*curr;
	t_list	*last;

	curr = *head;
	last = NULL;
	while (curr && curr->next)
	{
		if (curr->next->next == NULL)
		{
			last = curr->next;
			curr->next = NULL;
			break;
		}
	}
	last->next = *head;
	*head = last;
	printf("%s\n", s);
}

unsigned int	sqrt_of(unsigned int n)
{
	unsigned int i;

	i = 0;
	while (i * i < n)
		i++;
	return (i);
}

size_t	max_of(t_list *list)
{
	size_t	pos_of_max;

	pos_of_max = 0;
	while (list && list->next)
	{
		if (list->content >	list->next->content)
			pos_of_max++;
		else if (list->content < list->next->content)
			pos_of_max++;
		list = list->next;
	}
	return (pos_of_max);
}

void	chunk_sort(t_list **stack_a)
{
	t_list	*stack_b;
	size_t	n = ft_lstsize(*stack_a);
	size_t	chunk_size = sqrt_of(n);
	size_t	current_chunk;
	size_t	limit;
	size_t	pushed;
	size_t	pos;

	current_chunk = 0;
	pushed = 0;
	stack_b = NULL;
	while (n > chunk_size)
	{
		limit = (current_chunk + 1) * chunk_size;
		if ((size_t)(*stack_a)->index < limit)
		{
			*stack_a = push(*stack_a, &stack_b, "pa");
			if ((size_t)stack_b->index < limit - chunk_size / 2)
				r_ab(&stack_b, "rb");
			pushed++;
			if (pushed == (current_chunk + 1) * chunk_size)
				current_chunk++;
		}
		else
			r_ab(stack_a, "ra");
	}
	pos = 0;
	while (ft_lstsize(stack_b) > 0)
	{
		pos = max_of(stack_b);
		if (pos < ft_lstsize(stack_b) / 2)
			while (pos--)
				r_ab(&stack_b, "rb");
		else
			rr_ab(&stack_b, "rrb");
		stack_b = push(stack_b, stack_a, "pa");
	}
	
}

t_list	*min(t_list *list)
{
	t_list	*the_min;
	int		pos;

	the_min = list;
	pos = 0;
	while (list)
	{
		if (the_min->content > list->content && list->index == -1)
			the_min = list;
		list = list->next;
	}
	if (the_min->index != -1)
		return (NULL);
	return (the_min);
}

void	update_index(t_list *list)
{
	int		pos;
	t_list	*curr;

	pos = 0;
	while (1)
	{
		curr = min(list);
		if (curr == NULL)
			return ;
		curr->index = pos++;
	}
}

int main()
{
	int arr[10] = {10, 2, 4, 8, 3, -4, 0, 7, 6, 5};
	size_t count = 10;
	t_list	*stack_a = NULL;
	for (size_t i = 0; i < count; i++)
		ft_lstadd_back(&stack_a, ft_lstnew(arr[i]));
	update_index(stack_a);
	// bubble_sort(&stack_a); // ==> 79 moves / 12 vs 7
	chunk_sort(&stack_a);
	printf("\n");
	t_list *curr = stack_a;
	while (curr)
	{
		printf("%d ", (curr->content));
		curr = curr->next;
	}
	ft_lstclear(&stack_a);
}