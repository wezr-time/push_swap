#ifndef PUSH_SWAP
#define PUSH_SWAP

#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"



#include <stdio.h>

int		is_sort(t_list *head);

void	swap(t_list *node1, t_list *node2, char *s);
t_list	*push(t_list *node, t_list **head, char *s);
void	r_ab(t_list **head, char *s);
void	rr_ab(t_list **head, char *s);

void	bubble_sort(t_list **stack_a);
void	chunk_sort(t_list **stack_a);
void	radix_sort(t_list **stack_a);

#endif