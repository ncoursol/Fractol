NAME = fractol
FLAGS = -Wall -Wextra -Werror
CC = gcc

LIB_DIR = ./lib/libft
MINILIBX_DIR = ./lib/minilibx_linux
SRC_DIR = ./srcs
INCLUDE_DIR = ./includes

INCLUDE = $(INCLUDE_DIR)/fractol.h
SRC = $(SRC_DIR)/main.c
LIB = $(LIB_DIR)/libft.a
OBJ = $(SRC:.c=.o) 


all: $(NAME)

$(NAME): $(LIB) $(OBJ) $(INCLUDE)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIB) -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -lbsd -lpthread

$(LIB):
	make -C $(LIB_DIR)
	make -C $(MINILIBX_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(LIB_DIR)
	make clean -C $(MINILIBX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all

.PHONY: all clean fclean re
#.SILENT:
