CC = cc
CFLAGS = -lreadline -lhistory #-Wall -Wextra -Werror -ggdb

NAME = minishell

SRC = checknamelater.c main.c
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT = libft.a

LIBS = -lreadline -lncurses

# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)
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