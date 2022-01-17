SRC = $(wildcard ./*.c) \
	$(wildcard ./lexer/*.c) \

SRCS = $(filter-out %_test.c, $(SRC))
OBJS = $(SRCS:.c=.o)

all: minishell

minishell: $(OBJS)
	make -C ./libft
	gcc -fsanitize=address -o $@ $^ ./libft/libft.a -L/usr/include -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f minishell
