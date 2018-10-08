# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 11:45:07 by hsabouri          #+#    #+#              #
#    Updated: 2018/10/08 13:58:52 by hsabouri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
CFLAGS = -Wall -Wextra -I$(INCDIR)
#CFLAGS += -Werror
CFLAGS += -g #-fsanitize=address
CC = clang
SRCDIR = sources
SRCS = init.c mmap.c malloc.c free.c realloc.c calloc.c

SRC = $(SRCS:%.c=$(SRCDIR)/%.c)
TESTS = main.c
INCDIR = includes
INCS = malloc.h
OBJ	= $(SRC:$(SRCDIR)/%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -shared
	ln -s $(NAME) libft_malloc.so

test: $(OBJ) $(TESTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: $(SRCDIR)/%.c $(INCDIR)/$(INCS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf test.dSYM
	rm -f libft_malloc.so
	rm -f test

.PHONY: clean fclean re

re: fclean
	$(MAKE) all
