#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdlib.h>

typedef struct s_gb_collector
{
	void					*ptr;
	struct s_gb_collector	*next;
}	t_gb_collector;

void	clean_gb(t_gb_collector **gb_c);
void	*gb_malloc(size_t size, t_gb_collector **gb_c);
void	gb_free_node(void *ptr, t_gb_collector **gb_c);

#endif