# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 10:39:42 by lde-batz          #+#    #+#              #
#    Updated: 2021/03/16 15:33:57 by lde-batz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = woody_woodpacker

SRC +=	main.c
SRC +=	check_file.c
SRC +=	woody_woodpacker.c
SRC +=	encrypt.c
SRC +=	exit.c

SRC_DIR = srcs/

OBJ_DIR = objects/

OBJ := $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

SRC := $(addprefix $(SRC_DIR), $(SRC))

INC = includes

INCLUDES = $(INC)/woody.h

LIB = libft

INC_FLAG = -I$(INC) -I$(LIB)

LIB_FLAG = -L ./$(LIB) -lft

CC = gcc

CFLAGS += -Wall -Wextra
ifeq ($(d), 1)
	CFLAGS += -g3 -fsanitize=address,undefined
else ifeq ($(d), 2)
	CFLAGS += -g3 -fsanitize=address,undefined
	CFLAGS += -Wpadded -Wpedantic
endif
ifneq ($(err), no)
	CFLAGS += -Werror
endif 

GCC = $(CC) $(CFLAGS)

.SILENT:

all: lib $(NAME)

$(NAME): $(OBJ)
	$(GCC) $(INC_FLAG) -o $(NAME) $(SRC) $(LIB_FLAG)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Create woody_woodpacker"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDES) $(LIB)/libft.a
	mkdir -p $(OBJ_DIR)
	$(GCC) $(INC_FLAG) -c $< -o $@
	printf '\033[0m[ ✔ ] %s\n\033[0m' "$<"

lib:
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJ)
	rm -Rf $(OBJ_DIR)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean woody_woodpacker"

fclean: clean
	make -C libft fclean
	rm -f $(NAME) woody
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Fclean woody_woodpacker"

re: fclean all

.PHONY: all clean fclean re lib

