CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f

MAIN_SRC = push_swap.c
SRCS = helper/fill_stack_a.c \
		helper/ft_atoi.c \
		helper/ft_split.c \
		helper/ft_strlen.c \
		helper/ft_strncmp.c \
		helper/ft_lstsize.c \
		helper/is_sort.c \
		moves/rotate.c \
		moves/reverse_rotate.c \
		moves/push.c \
		garbage_collector/garbage_collector.c \
		sort_algo/selection_sort.c \
		sort_algo/chunk_sort.c

HEADERS = push_swap.h garbage_collector/garbage_collector.h 

OBJ_MAIN = $(MAIN_SRC:.c=.o)
OBJ_SRCS = $(SRCS:.c=.o)

NAME = push_swap

All: $(NAME)

$(NAME): $(OBJ_MAIN) $(OBJ_SRCS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $HEADERS
	$(CC) $(CFLAGS) $^ -c $@

clean:
	$(RM) $(OBJ_MAIN) $(OBJ_SRCS)

fclean: clean
	$(RM) $(NAME)

re: fclean All

.PHONY: clean
