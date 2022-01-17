# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 06:15:47 by rnishimo          #+#    #+#              #
#    Updated: 2022/01/17 06:15:48 by rnishimo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = $(wildcard ./*.c) \
	$(wildcard ./lexer/*.c) \
	$(wildcard ./parser/*.c) \

SRCS = $(filter-out %_test.c, $(SRC))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	gcc -fsanitize=address -o $@ $^ ./libft/libft.a -L/usr/include -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	@echo ------test------
	@cd lexer && make test
	@cd parser && make test
	@echo -------OK-------

.PHONY: all clean fclean re test
