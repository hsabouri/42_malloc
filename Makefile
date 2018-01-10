# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 11:45:07 by hsabouri          #+#    #+#              #
#    Updated: 2018/01/10 10:36:31 by hsabouri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc$(HOSTTYPE).so
CFLAGS = -Wall -Wextra -Werror -I$(INC)
#CFLAGS += -g -fsanitize=address
CC = clang
SRCDIR = sources
SRCS = init.c\
	   history.c\
	   free.c\
	   history.c\
	   malloc.c\
	   show_alloc_mem.c\
	   search.c\
	   display.c\
	   history.c

TESTS = main.c
SRC = $(SRCS:%.c=$(SRCDIR)/%.c)
INC = includes
OBJ	= $(SRC:$(SRCDIR)/%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
ifdef HISTORY
	$(CC) -o $@ $< -I$(INC)/ $(CFLAGS) -shared -D HISTORY
else
	$(CC) -o $@ $< -I$(INC)/ $(CFLAGS) -shared
endif
	ln -s $(NAME) libft_malloc.so

test: $(OBJ) 
ifdef HISTORY
	$(CC) -o $@ $< $(SRCDIR)/$(TESTS) -I$(INC)/ $(CFLAGS) -D HISTORY
else
	$(CC) -o $@ $< $(SRCDIR)/$(TESTS) -I$(INC)/ $(CFLAGS)
endif

%.o: $(SRCDIR)/%.c
ifdef HISTORY
	$(CC) $(CFLAGS) -o $@ -c $< -D HISTORY
else
	$(CC) $(CFLAGS) -o $@ -c $<
endif

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -f libft_malloc.so

.PHONY: clean fclean re

re: fclean
	$(MAKE) all
