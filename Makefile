NAME = ft_ls
LIBFT_NAME = libft.a

SRC_PATH = src/
SRC_P_PATH = src/parse/
SRC_R_P = src/render/
INC_PATH = inc/
LIB_PATH = libft/

SRC =       main.c \

SRC_PARSE =

SRC_RENDER =

OBJ_DIR = obj

SDL_CFLAGS = $(shell sdl2-config --cflags)

OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_SRC_P = $(addprefix $(OBJ_DIR)/, $(SRC_PARSE:.c=.o))

OBJ_SRC_R_P = $(addprefix $(OBJ_DIR)/, $(SRC_RENDER:.c=.o))

CC	= gcc
FLG = -Werror -Wextra -Wall

all: $(NAME)

$(NAME): $(OBJ_SRC)
	@make -C $(LIB_PATH)
	@$(CC) -O3 $(FLG) -g $(LIB_PATH)$(LIBFT_NAME) $(OBJ_SRC) -o $(NAME)

$(OBJ_DIR)/%.o : ./src/%.c
	@/bin/mkdir -p $(OBJ_DIR)
	@$(CC) $(FLG) -g -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/parse/%.c
	@$(CC) $(FLG) -g -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/sdl_f/%.c
	@$(CC) $(FLG) -g -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/render/%.c
	@$(CC) $(FLG) -g -I./inc -c -o $@ $<

$(OBJ_DIR)/%.o : ./src/sdl/%.c
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
