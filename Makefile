# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 08:09:39 by mjuncker          #+#    #+#              #
#    Updated: 2024/11/23 10:06:00 by mchemari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_shmup
CFLAGS = -Wall -Wextra -Werror -g3 $(INCLUDES_D)

SRC = main.c entities.c
OBJ = $(SRC:.c=.o)

OBJ_D = obj/
SRCS_D = src/
BIN_D = bin/
INCLUDES_D = -Iincludes/ -Ilibft/includes/

OBJ := $(addprefix $(OBJ_D), $(OBJ))
SRCS := $(addprefix $(SRCS_D), $(SRCS))

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -lncurses $(OBJ) libft/bin/libft.a -o $(NAME)


$(OBJ_D)%.o : $(SRCS_D)%.c includes/shmup.h | $(OBJ_D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJ)

.PHONY: fclean
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) re -C ./libft
	$(MAKE) all

run: all
	./ft_shmup

# Create directories
$(OBJ_D):
	mkdir -p $(OBJ_D)

$(BIN_D):
	mkdir -p $(BIN_D)
