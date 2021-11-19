# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 12:47:22 by ohachim           #+#    #+#              #
#    Updated: 2021/11/19 16:33:44 by ohachim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

SRC_PATH = src

SRC_NAME = error.c main.c my_atoi.c my_strlen.c philo_actions.c \
	philosopher_init.c threads.c ft_putchar.c ft_putnbr.c death.c \
	ft_putstr.c time.c del_mem.c eat.c

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

INC = includes

HEADER_NAME = hphilosophers.h

HEADER = $(addprefix $(INC)/, $(HEADER_NAME))

CFLAGS = -pthread -Wall -Wextra -Werror

TARGET = philosopher

.PHONY: all, clean, fclean, re

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC)  $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) -I $(INC) -o $@ -c $<

clean:
	@rm -vf $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@rm -vf $(TARGET)

re: fclean all