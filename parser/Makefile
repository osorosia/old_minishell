# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 06:22:21 by rnishimo          #+#    #+#              #
#    Updated: 2022/01/17 06:54:28 by rnishimo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OBJS += $(filter-out %_test.o, $(wildcard ../lexer/*.o))
# OBJS += $(filter-out %_test.o, $(wildcard ../parser/*.o))
OBJS += $(filter-out %_test.o, $(wildcard ../expander/*.o))
OBJS += $(filter-out %_test.o, $(wildcard ../exec/*.o))

all: $(NAME)

$(NAME): $(OBJS) ../minishell.h
	make -C ../
	gcc $(OBJS) ../libft/libft.a

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME)

.PHONY: all clean fclean re
