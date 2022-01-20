# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 06:15:53 by rnishimo          #+#    #+#              #
#    Updated: 2022/01/20 10:58:17 by rnishimo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OBJS += $(filter-out %main.o, $(wildcard ../*.o))
OBJS += $(filter-out %_test.o, $(wildcard ../lexer/*.o))
OBJS += $(filter-out %_test.o, $(wildcard ../parser/*.o))
OBJS += $(filter-out %_test.o, $(wildcard ../expander/*.o))
OBJS += $(filter-out %_test.o, $(wildcard ../exec/*.o))
OBJS += $(filter-out %_test.o, $(wildcard ../ms/*.o))
# OBJS += $(filter-out %_test.o, $(wildcard ../builtin/*.o))

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
