#include "garbage_collector.h"

void	clean_gb(t_gb_collector **gb_c)
{
	t_gb_collector	*tmp;

	while (*gb_c)
	{
		tmp = (*gb_c)->next;
		free((*gb_c)->ptr);
		free(*gb_c);
		*gb_c = tmp;
	}
	*gb_c = NULL;
}

void	gb_free_node(void *ptr, t_gb_collector **gb_c)
{
	t_gb_collector	*tmp;

	while (*gb_c)
	{
		if ((*gb_c)->ptr == ptr)
		{
			tmp = (*gb_c)->next;
			free((*gb_c)->ptr);
			free((*gb_c));
			*gb_c = tmp;
			return ;
		}
		else
			gb_c = &(*gb_c)->next;
	}
}

void	*gb_malloc(size_t size, t_gb_collector **gb_c)
{
	t_gb_collector	*new_node;

	new_node = malloc(sizeof(t_gb_collector));
	if (!new_node)
		return (NULL);
	new_node->ptr = malloc(size);
	if (!new_node->ptr)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = *gb_c;
	*gb_c = new_node;
	return (new_node->ptr);
}
