#ifndef PUSH_SWAP
#define PUSH_SWAP

#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"


typedef struct s_count
{
	int		pa;
	int		pb;
	int		sa;
	int		sb;
	int		ra;
	int		rb;
	int		rrb;
	float	disorder;
}	t_count;

#include <stdio.h>

int		is_sort(t_list *head);

void	swap(t_list *node1, t_list *node2, char *s);
t_list	*push(t_list *node, t_list **head, char *s);
void	r_ab(t_list **head, char *s);
void	rr_ab(t_list **head, char *s);

void	bubble_sort(t_list **stack_a, t_count *count_op);
void	chunk_sort(t_list **stack_a, t_count *count_op);
void	radix_sort(t_list **stack_a, t_count *count_op);

float	compute_disorder(t_list *stack_a);
void	update_index(t_list *list);

#endif