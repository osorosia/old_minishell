# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 06:15:47 by rnishimo          #+#    #+#              #
#    Updated: 2022/01/21 00:37:59 by rnishimo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = $(wildcard ./*.c) \
	$(wildcard ./lexer/*.c) \
	$(wildcard ./parser/*.c) \
	$(wildcard ./expander/*.c) \
	$(wildcard ./exec/*.c) \
	$(wildcard ./ms/*.c) \
	$(wildcard ./builtin/*.c) \

SRCS = $(filter-out %_test.c, $(SRC))
OBJS = $(SRCS:.c=.o)
CFLAGS = 
# CFLAGS = -fsanitize=address

all: $(NAME)

run: re
	./$(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	gcc $(CFLAGS) -o $@ $^ ./libft/libft.a -L/usr/include -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	cd lexer && make fclean
	cd parser && make fclean
	cd expander && make fclean
	cd exec && make fclean
	cd ms && make fclean

re: fclean all

test: all
	@echo ------test------
	@cd lexer && make test
	@cd parser && make test
	@cd expander && make test
	@cd exec && make test
	@cd ms && make test
	@echo -------OK-------

t:
	cd temp && gcc temp.c && ./a.out

.PHONY: all clean fclean re test
