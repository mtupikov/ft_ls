NAME = ft_ls
LIBFT_NAME = libft.a

SRC_PATH = src/
INC_PATH = inc/
LIB_PATH = libft/

SRC =   main.c \
        main_utils.c \
        ft_ls_algorithm.c \
        file_management.c \
        buffer_management.c \
        sorting_management.c \
        sort_cmp_functions.c \
        printing_management.c \

OBJ_DIR = obj

SDL_CFLAGS = $(shell sdl2-config --cflags)

OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CC	= gcc
FLG = -Werror -Wextra -Wall

all: $(NAME)

$(NAME): $(OBJ_SRC)
	@make -C $(LIB_PATH)
	@$(CC) -O3 $(FLG) -g $(LIB_PATH)$(LIBFT_NAME) $(OBJ_SRC) -o $(NAME)

$(OBJ_DIR)/%.o : ./src/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) -g -I./inc -c -o $@ $<

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make -C $(LIB_PATH) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIB_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
