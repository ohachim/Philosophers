# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 12:47:22 by ohachim           #+#    #+#              #
#    Updated: 2021/10/12 17:40:12 by ohachim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

SRC_PATH = src

SRC_NAME = error.c main.c my_atoi.c my_strdup.c my_strlen.c philo_actions.c philosopher_init.c threads.c

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

INC = includes

# CFLAGS = -pthread -Wall -Wextra -Werror
CFLAGS =

TARGET = philosopher

.PHONY: all, clean, fclean, re

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC)  $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) -I $(INC) -o $@ -c $<

clean:
	@rm -vf $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@rm -vf $(TARGET)

re: fclean all