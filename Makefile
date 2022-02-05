NAME := fractol

INCLUDE_FOLDERS := -I includes/ -I lib/libft/includes/ -I lib/minilibx_macos/
SOURCES_FOLDER  := srcs/
OBJECTS_FOLDER  := objs/

vpath %.c srcs

CC := gcc
FLAGS := -Wall -Wextra -Werror -Ofast
MLX := -framework OpenGL -framework AppKit
THREAD := -lpthread

SOURCES := ./srcs/main.c\
	  ./srcs/event.c\
	  ./srcs/event_fct.c\
	  ./srcs/fractal.c\
	  ./srcs/init.c\
	  ./srcs/utils.c\
	  ./srcs/utils2.c\

OBJECTS := $(SOURCES:.c=.o)

OBJECTS := $(addprefix $(OBJECTS_FOLDER), $(OBJECTS))
SOURCES := $(addprefix $(SOURCES_FOLDER), $(SOURCES))

all: $(NAME)

$(NAME): $(OBJECTS) ./includes/fractol.h
	@make -C lib/libft/ -s
	@make -C lib/minilibx_macos/ -s
	@$(CC) -o $(NAME) $(OBJECTS) $(FLAGS) lib/libft/libft.a $(MLX) $(THREAD) \
	lib/minilibx_macos/libmlx.a

objs/%.o: %.c ./includes/fractol.h 
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDE_FOLDERS) -c $< -o $@
clean:
	@make -C lib/libft/ clean -s
	@make -C lib/minilibx_macos clean -s
	@rm -rf $(OBJECTS_FOLDER)

fclean: clean
	@make -C lib/libft/ fclean -s
	@rm -f $(NAME)

re:
	@make fclean
	@make

.PHONY: all clean fclean re header
.SILENT:
