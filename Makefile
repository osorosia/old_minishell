SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: minishell

minishell: $(OBJS)
	gcc -o $@ $^ ./libft/libft.a

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f minishell

