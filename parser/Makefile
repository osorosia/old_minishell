NAME = a.out
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OBJS += $(filter-out %_test.o, $(wildcard ../lexer/*.o))

all: $(NAME)

$(NAME): $(OBJS) ../minishell.h
	make -C ../
	gcc $^ ../libft/libft.a

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME)

.PHONY: all clean fclean re
