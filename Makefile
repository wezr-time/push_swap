SRCS		= push_swap.c \
			selection_sort.c \
			chunk_sort.c \
			radix_sort.c \
			ft_flag.c \
			ft_sort.c \
			ft_split.c \
			ft_stack_fill.c \
			ft_dprintf.c \
			ft_push.c \
			ft_swap.c \
			ft_rotate.c \
			ft_reverce_rotate.c \
			utils_1.c \
			utils_2.c \
			utils_3.c \
			utils_4.c \
			utils_5.c \

SRCS_BNS	= checker.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_dprintf_bonus.c \
			ft_push_bonus.c \
			ft_swap_bonus.c \
			ft_rotate_bonus.c \
			ft_reverce_rotate_bonus.c \
			ft_stack_fill_bonus.c \
			ft_split_bonus.c \
			ft_ops_bonus.c \
			utils_0_bonus.c \
			utils_1_bonus.c \
			utils_2_bonus.c \
			utils_3_bonus.c \
			utils_4_bonus.c \
			utils_5_bonus.c

NAME		= push_swap
NAME_BNS	= checker

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

HEADER		= push_swap.h
HEADER_BNS	= checker.h

OBJ			= $(SRCS:.c=.o)
OBJ_BNS		= $(SRCS_BNS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@

bonus: $(NAME_BNS)

$(NAME_BNS): $(OBJ_BNS)
	@$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADER) $(HEADER_BNS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ) $(OBJ_BNS)

fclean: clean
	@$(RM) $(NAME) $(NAME_BNS)

re: fclean all

.PHONY: all bonus clean fclean re