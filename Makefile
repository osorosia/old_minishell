# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 06:15:47 by rnishimo          #+#    #+#              #
#    Updated: 2022/01/27 12:31:30 by rnishimo         ###   ########.fr        #
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
# CFLAGS = -fsanitize=address
ifeq ($(findstring debug, $(MAKECMDGOALS)), debug)
DEBUG = -D DEBUG=1
endif

$(NAME): $(OBJS)
	make -C ./libft
	gcc $(CFLAGS) $(DEBUG) -o $@ $^ ./libft/libft.a -L/usr/include -lreadline

%.o: %.c
	gcc $(CFLAGS) $(DEBUG) -c -o $@ $<

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	cd lexer && make fclean
	cd parser && make fclean
	cd expander && make fclean
	cd exec && make fclean
	cd ms && make fclean

.PHONY: re
re: fclean all

.PHONY: debug
debug: re

.PHONY: test
test: all
	@echo ------test------
	@cd lexer && make test
	@cd parser && make test
	@cd expander && make test
	@cd exec && make test
	@cd ms && make test
	@echo -------OK-------

.PHONY: t
t:
	cd temp && gcc temp.c && ./a.out

