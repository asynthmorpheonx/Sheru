CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = minishell

SRC = checknamelater.c main.c
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT = libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "minishell built successfully!"

$(LIBFT):
	@make -C libft bonus

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

.SECONDARY : $(OBJ)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -s -C libft clean
	@echo "Object files removed"

fclean:
	@rm -rf $(OBJ_DIR)
	@make -s -C libft clean
	@rm -f $(NAME)
	@echo "minishell removed"

re: fclean all

.PHONY: all clean fclean re