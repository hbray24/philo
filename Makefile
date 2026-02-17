NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lpthread

SRCS =	main.c \
		parsing.c \
		time.c \
		utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re