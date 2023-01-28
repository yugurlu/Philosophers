NAME = philo
CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS = main.c \
	routine.c \
	error.c \

OBJS = $(SRCS:.c=.o)

PINK		:= \033[1;45m
PINK2		:= \033[0;35;5;199m

all: $(NAME)
	@echo "$(PINK)Compile Completed!"

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS)

.c.o:
	@echo "$(PINK2)Complining: $<"
	@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
