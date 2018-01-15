# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 11:45:07 by hsabouri          #+#    #+#              #
#    Updated: 2018/01/15 20:31:27 by hsabouri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc$(HOSTTYPE).so
CFLAGS = -Wall -Wextra -I$(INCDIR)
CFLAGS += -Werror
#CFLAGS += -g -fsanitize=address
CC = clang
SRCDIR = sources
SRCS = init.c\
	   history.c\
	   free.c\
	   malloc.c\
	   realloc.c\
	   show_alloc_mem.c\
	   search.c\
	   display.c\
	   display2.c\
	   history.c\
	   tools.c

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

inject: all
	export DYLD_LIBRARY_PATH=.
	export DYLD_INSERT_LIBRARIES=$(NAME)
	export DYLD_FORCE_FLAT_NAMESPACE=1

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -f libft_malloc.so
	rm -f test

.PHONY: clean fclean re

re: fclean
	$(MAKE) all
