#include "push_swap.h"

void r_ab(t_list **head, char *s)
{
	t_list *first;
	t_list	*curr;

	curr = *head;
	first = *head;
	*head = (*head)->next;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = first;
	first->next = NULL;
	printf("%s\n", s);
}

void rr_ab(t_list **head, char *s)
{
	t_list *curr;
	t_list *last;

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
		curr = curr->next;
	}
	last->next = *head;
	*head = last;
	printf("%s\n", s);
}

void	swap(t_list *node1, t_list *node2, char *s)
{
	int tmp = node1->content;
	node1->content = node2->content;
	node2->content = tmp;
	printf("%s\n", s);
}

t_list	*push(t_list *node, t_list **head, char *s)
{
	t_list	*tmp;

	tmp = node->next;
	node->next = *head;
	*head = node;
	printf("%s\n", s);
	return (tmp);
}
