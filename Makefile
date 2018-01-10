# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 11:45:07 by hsabouri          #+#    #+#              #
#    Updated: 2018/01/10 16:55:06 by hsabouri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc$(HOSTTYPE).so
CFLAGS = -Wall -Wextra -I$(INC)
CFLAGS += -Werror
CFLAGS += -g -fsanitize=address
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
	   history.c\
	   tools.c

TESTS = main.c
SRC = $(SRCS:%.c=$(SRCDIR)/%.c)
INC = includes
OBJ	= $(SRC:$(SRCDIR)/%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
ifdef HISTORY
	$(CC) -o $@ $^ $(CFLAGS) -shared -D HISTORY
else
	$(CC) -o $@ $^ $(CFLAGS) -shared
endif
	ln -s $(NAME) libft_malloc.so

test: $(OBJ) $(SRCDIR)/$(TESTS)
ifdef HISTORY
	$(CC) -o $@ $^ $(CFLAGS) -D HISTORY
else
	$(CC) -o $@ $^ $(SRCDIR)/$(TESTS) $(CFLAGS)
endif

%.o: $(SRCDIR)/%.c
ifdef HISTORY
	$(CC) $(CFLAGS) -o $@ -c $< -D HISTORY
else
	$(CC) $(CFLAGS) -o $@ -c $<
endif

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
